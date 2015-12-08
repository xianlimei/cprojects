#ifndef SQLITE_OMIT_VIRTUALTABLE
if(  (pLoop->wsFlags & WHERE_VIRTUALTABLE)!=0 ){
    /* Case 1:  The table is a virtual-table.  Use the VFilter and VNext
    **          to access the data.
    */
    int iReg;   /* P3 Value for OP_VFilter */
    int addrNotFound;
    int nConstraint = pLoop->nLTerm;

    sqlite3ExprCachePush(pParse);
    iReg = sqlite3GetTempRange(pParse, nConstraint+2);
    addrNotFound = pLevel->addrBrk;
    for(j=0; j<nConstraint; j++){
      int iTarget = iReg+j+2;
      pTerm = pLoop->aLTerm[j];
      if( pTerm==0 ) continue;
      if( pTerm->eOperator & WO_IN ){
        codeEqualityTerm(pParse, pTerm, pLevel, j, bRev, iTarget);
        addrNotFound = pLevel->addrNxt;
      }else{
        sqlite3ExprCode(pParse, pTerm->pExpr->pRight, iTarget);
      }
    }
    sqlite3VdbeAddOp2(v, OP_Integer, pLoop->u.vtab.idxNum, iReg);
    sqlite3VdbeAddOp2(v, OP_Integer, nConstraint, iReg+1);
    sqlite3VdbeAddOp4(v, OP_VFilter, iCur, addrNotFound, iReg,
                      pLoop->u.vtab.idxStr,
                      pLoop->u.vtab.needFree ? P4_MPRINTF : P4_STATIC);
    VdbeCoverage(v);
    pLoop->u.vtab.needFree = 0;
    for(j=0; j<nConstraint && j<16; j++){
      if( (pLoop->u.vtab.omitMask>>j)&1 ){
        disableTerm(pLevel, pLoop->aLTerm[j]);
      }
    }
    pLevel->p1 = iCur;
    pLevel->op = pWInfo->eOnePass ? OP_Noop : OP_VNext;
    pLevel->p2 = sqlite3VdbeCurrentAddr(v);
    sqlite3ReleaseTempRange(pParse, iReg, nConstraint+2);
    sqlite3ExprCachePop(pParse);
  }else
#endif /* SQLITE_OMIT_VIRTUALTABLE */

  if( (pLoop->wsFlags & WHERE_IPK)!=0
   && (pLoop->wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_EQ))!=0
  ){
    /* Case 2:  We can directly reference a single row using an
    **          equality comparison against the ROWID field.  Or
    **          we reference multiple rows using a "rowid IN (...)"
    **          construct.
    */
    assert( pLoop->u.btree.nEq==1 );
    pTerm = pLoop->aLTerm[0];
    assert( pTerm!=0 );
    assert( pTerm->pExpr!=0 );
    assert( omitTable==0 );
    testcase( pTerm->wtFlags & TERM_VIRTUAL );
    iReleaseReg = ++pParse->nMem;
    iRowidReg = codeEqualityTerm(pParse, pTerm, pLevel, 0, bRev, iReleaseReg);
    if( iRowidReg!=iReleaseReg ) sqlite3ReleaseTempReg(pParse, iReleaseReg);
    addrNxt = pLevel->addrNxt;
    sqlite3VdbeAddOp2(v, OP_MustBeInt, iRowidReg, addrNxt); VdbeCoverage(v);
    sqlite3VdbeAddOp3(v, OP_NotExists, iCur, addrNxt, iRowidReg);
    VdbeCoverage(v);
    sqlite3ExprCacheAffinityChange(pParse, iRowidReg, 1);
    sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
    VdbeComment((v, "pk"));
    pLevel->op = OP_Noop;
  }else if( (pLoop->wsFlags & WHERE_IPK)!=0
         && (pLoop->wsFlags & WHERE_COLUMN_RANGE)!=0
  ){
    /* Case 3:  We have an inequality comparison against the ROWID field.
    */
    int testOp = OP_Noop;
    int start;
    int memEndValue = 0;
    WhereTerm *pStart, *pEnd;

    assert( omitTable==0 );
    j = 0;
    pStart = pEnd = 0;
    if( pLoop->wsFlags & WHERE_BTM_LIMIT ) pStart = pLoop->aLTerm[j++];
    if( pLoop->wsFlags & WHERE_TOP_LIMIT ) pEnd = pLoop->aLTerm[j++];
    assert( pStart!=0 || pEnd!=0 );
    if( bRev ){
      pTerm = pStart;
      pStart = pEnd;
      pEnd = pTerm;
    }
    if( pStart ){
      Expr *pX;             /* The expression that defines the start bound */
      int r1, rTemp;        /* Registers for holding the start boundary */

      /* The following constant maps TK_xx codes into corresponding 
      ** seek opcodes.  It depends on a particular ordering of TK_xx
      */
      const u8 aMoveOp[] = {
           /* TK_GT */  OP_SeekGT,
           /* TK_LE */  OP_SeekLE,
           /* TK_LT */  OP_SeekLT,
           /* TK_GE */  OP_SeekGE
      };
      assert( TK_LE==TK_GT+1 );      /* Make sure the ordering.. */
      assert( TK_LT==TK_GT+2 );      /*  ... of the TK_xx values... */
      assert( TK_GE==TK_GT+3 );      /*  ... is correcct. */

      assert( (pStart->wtFlags & TERM_VNULL)==0 );
      testcase( pStart->wtFlags & TERM_VIRTUAL );
      pX = pStart->pExpr;
      assert( pX!=0 );
      testcase( pStart->leftCursor!=iCur ); /* transitive constraints */
      r1 = sqlite3ExprCodeTemp(pParse, pX->pRight, &rTemp);
      sqlite3VdbeAddOp3(v, aMoveOp[pX->op-TK_GT], iCur, addrBrk, r1);
      VdbeComment((v, "pk"));
      VdbeCoverageIf(v, pX->op==TK_GT);
      VdbeCoverageIf(v, pX->op==TK_LE);
      VdbeCoverageIf(v, pX->op==TK_LT);
      VdbeCoverageIf(v, pX->op==TK_GE);
      sqlite3ExprCacheAffinityChange(pParse, r1, 1);
      sqlite3ReleaseTempReg(pParse, rTemp);
      disableTerm(pLevel, pStart);
    }else{
      sqlite3VdbeAddOp2(v, bRev ? OP_Last : OP_Rewind, iCur, addrBrk);
      VdbeCoverageIf(v, bRev==0);
      VdbeCoverageIf(v, bRev!=0);
    }
    if( pEnd ){
      Expr *pX;
      pX = pEnd->pExpr;
      assert( pX!=0 );
      assert( (pEnd->wtFlags & TERM_VNULL)==0 );
      testcase( pEnd->leftCursor!=iCur ); /* Transitive constraints */
      testcase( pEnd->wtFlags & TERM_VIRTUAL );
      memEndValue = ++pParse->nMem;
      sqlite3ExprCode(pParse, pX->pRight, memEndValue);
      if( pX->op==TK_LT || pX->op==TK_GT ){
        testOp = bRev ? OP_Le : OP_Ge;
      }else{
        testOp = bRev ? OP_Lt : OP_Gt;
      }
      disableTerm(pLevel, pEnd);
    }
    start = sqlite3VdbeCurrentAddr(v);
    pLevel->op = bRev ? OP_Prev : OP_Next;
    pLevel->p1 = iCur;
    pLevel->p2 = start;
    assert( pLevel->p5==0 );
    if( testOp!=OP_Noop ){
      iRowidReg = ++pParse->nMem;
      sqlite3VdbeAddOp2(v, OP_Rowid, iCur, iRowidReg);
      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
      sqlite3VdbeAddOp3(v, testOp, memEndValue, addrBrk, iRowidReg);
      VdbeCoverageIf(v, testOp==OP_Le);
      VdbeCoverageIf(v, testOp==OP_Lt);
      VdbeCoverageIf(v, testOp==OP_Ge);
      VdbeCoverageIf(v, testOp==OP_Gt);
      sqlite3VdbeChangeP5(v, SQLITE_AFF_NUMERIC | SQLITE_JUMPIFNULL);
    }
  }else if( pLoop->wsFlags & WHERE_INDEXED ){
    /* Case 4: A scan using an index.
    **
    **         The WHERE clause may contain zero or more equality 
    **         terms ("==" or "IN" operators) that refer to the N
    **         left-most columns of the index. It may also contain
    **         inequality constraints (>, <, >= or <=) on the indexed
    **         column that immediately follows the N equalities. Only 
    **         the right-most column can be an inequality - the rest must
    **         use the "==" and "IN" operators. For example, if the 
    **         index is on (x,y,z), then the following clauses are all 
    **         optimized:
    **
    **            x=5
    **            x=5 AND y=10
    **            x=5 AND y<10
    **            x=5 AND y>5 AND y<10
    **            x=5 AND y=5 AND z<=10
    **
    **         The z<10 term of the following cannot be used, only
    **         the x=5 term:
    **
    **            x=5 AND z<10
    **
    **         N may be zero if there are inequality constraints.
    **         If there are no inequality constraints, then N is at
    **         least one.
    **
    **         This case is also used when there are no WHERE clause
    **         constraints but an index is selected anyway, in order
    **         to force the output order to conform to an ORDER BY.
    */  
    static const u8 aStartOp[] = {
      0,
      0,
      OP_Rewind,           /* 2: (!start_constraints && startEq &&  !bRev) */
      OP_Last,             /* 3: (!start_constraints && startEq &&   bRev) */
      OP_SeekGT,           /* 4: (start_constraints  && !startEq && !bRev) */
      OP_SeekLT,           /* 5: (start_constraints  && !startEq &&  bRev) */
      OP_SeekGE,           /* 6: (start_constraints  &&  startEq && !bRev) */
      OP_SeekLE            /* 7: (start_constraints  &&  startEq &&  bRev) */
    };
    static const u8 aEndOp[] = {
      OP_IdxGE,            /* 0: (end_constraints && !bRev && !endEq) */
      OP_IdxGT,            /* 1: (end_constraints && !bRev &&  endEq) */
      OP_IdxLE,            /* 2: (end_constraints &&  bRev && !endEq) */
      OP_IdxLT,            /* 3: (end_constraints &&  bRev &&  endEq) */
    };
    u16 nEq = pLoop->u.btree.nEq;     /* Number of == or IN terms */
    int regBase;                 /* Base register holding constraint values */
    WhereTerm *pRangeStart = 0;  /* Inequality constraint at range start */
    WhereTerm *pRangeEnd = 0;    /* Inequality constraint at range end */
    int startEq;                 /* True if range start uses ==, >= or <= */
    int endEq;                   /* True if range end uses ==, >= or <= */
    int start_constraints;       /* Start of range is constrained */
    int nConstraint;             /* Number of constraint terms */
    Index *pIdx;                 /* The index we will be using */
    int iIdxCur;                 /* The VDBE cursor for the index */
    int nExtraReg = 0;           /* Number of extra registers needed */
    int op;                      /* Instruction opcode */
    char *zStartAff;             /* Affinity for start of range constraint */
    char cEndAff = 0;            /* Affinity for end of range constraint */
    u8 bSeekPastNull = 0;        /* True to seek past initial nulls */
    u8 bStopAtNull = 0;          /* Add condition to terminate at NULLs */

    pIdx = pLoop->u.btree.pIndex;
    iIdxCur = pLevel->iIdxCur;
    assert( nEq>=pLoop->nSkip );

    /* If this loop satisfies a sort order (pOrderBy) request that 
    ** was passed to this function to implement a "SELECT min(x) ..." 
    ** query, then the caller will only allow the loop to run for
    ** a single iteration. This means that the first row returned
    ** should not have a NULL value stored in 'x'. If column 'x' is
    ** the first one after the nEq equality constraints in the index,
    ** this requires some special handling.
    */
    assert( pWInfo->pOrderBy==0
         || pWInfo->pOrderBy->nExpr==1
         || (pWInfo->wctrlFlags&WHERE_ORDERBY_MIN)==0 );
    if( (pWInfo->wctrlFlags&WHERE_ORDERBY_MIN)!=0
     && pWInfo->nOBSat>0
     && (pIdx->nKeyCol>nEq)
    ){
      assert( pLoop->nSkip==0 );
      bSeekPastNull = 1;
      nExtraReg = 1;
    }

    /* Find any inequality constraint terms for the start and end 
    ** of the range. 
    */
    j = nEq;
    if( pLoop->wsFlags & WHERE_BTM_LIMIT ){
      pRangeStart = pLoop->aLTerm[j++];
      nExtraReg = 1;
      /* Like optimization range constraints always occur in pairs */
      assert( (pRangeStart->wtFlags & TERM_LIKEOPT)==0 || 
              (pLoop->wsFlags & WHERE_TOP_LIMIT)!=0 );
    }
    if( pLoop->wsFlags & WHERE_TOP_LIMIT ){
      pRangeEnd = pLoop->aLTerm[j++];
      nExtraReg = 1;
      if( (pRangeEnd->wtFlags & TERM_LIKEOPT)!=0 ){
        assert( pRangeStart!=0 );                     /* LIKE opt constraints */
        assert( pRangeStart->wtFlags & TERM_LIKEOPT );   /* occur in pairs */
        pLevel->iLikeRepCntr = ++pParse->nMem;
        testcase( bRev );
        testcase( pIdx->aSortOrder[nEq]==SQLITE_SO_DESC );
        sqlite3VdbeAddOp2(v, OP_Integer,
                          bRev ^ (pIdx->aSortOrder[nEq]==SQLITE_SO_DESC),
                          pLevel->iLikeRepCntr);
        VdbeComment((v, "LIKE loop counter"));
        pLevel->addrLikeRep = sqlite3VdbeCurrentAddr(v);
      }
      if( pRangeStart==0
       && (j = pIdx->aiColumn[nEq])>=0 
       && pIdx->pTable->aCol[j].notNull==0
      ){
        bSeekPastNull = 1;
      }
    }
    assert( pRangeEnd==0 || (pRangeEnd->wtFlags & TERM_VNULL)==0 );

    /* Generate code to evaluate all constraint terms using == or IN
    ** and store the values of those terms in an array of registers
    ** starting at regBase.
    */
    regBase = codeAllEqualityTerms(pParse,pLevel,bRev,nExtraReg,&zStartAff);
    assert( zStartAff==0 || sqlite3Strlen30(zStartAff)>=nEq );
    if( zStartAff ) cEndAff = zStartAff[nEq];
    addrNxt = pLevel->addrNxt;

    /* If we are doing a reverse order scan on an ascending index, or
    ** a forward order scan on a descending index, interchange the 
    ** start and end terms (pRangeStart and pRangeEnd).
    */
    if( (nEq<pIdx->nKeyCol && bRev==(pIdx->aSortOrder[nEq]==SQLITE_SO_ASC))
     || (bRev && pIdx->nKeyCol==nEq)
    ){
      SWAP(WhereTerm *, pRangeEnd, pRangeStart);
      SWAP(u8, bSeekPastNull, bStopAtNull);
    }

    testcase( pRangeStart && (pRangeStart->eOperator & WO_LE)!=0 );
    testcase( pRangeStart && (pRangeStart->eOperator & WO_GE)!=0 );
    testcase( pRangeEnd && (pRangeEnd->eOperator & WO_LE)!=0 );
    testcase( pRangeEnd && (pRangeEnd->eOperator & WO_GE)!=0 );
    startEq = !pRangeStart || pRangeStart->eOperator & (WO_LE|WO_GE);
    endEq =   !pRangeEnd || pRangeEnd->eOperator & (WO_LE|WO_GE);
    start_constraints = pRangeStart || nEq>0;

    /* Seek the index cursor to the start of the range. */
    nConstraint = nEq;
    if( pRangeStart ){
      Expr *pRight = pRangeStart->pExpr->pRight;
      sqlite3ExprCode(pParse, pRight, regBase+nEq);
      whereLikeOptimizationStringFixup(v, pLevel, pRangeStart);
      if( (pRangeStart->wtFlags & TERM_VNULL)==0
       && sqlite3ExprCanBeNull(pRight)
      ){
        sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
        VdbeCoverage(v);
      }
      if( zStartAff ){
        if( sqlite3CompareAffinity(pRight, zStartAff[nEq])==SQLITE_AFF_BLOB){
          /* Since the comparison is to be performed with no conversions
          ** applied to the operands, set the affinity to apply to pRight to 
          ** SQLITE_AFF_BLOB.  */
          zStartAff[nEq] = SQLITE_AFF_BLOB;
        }
        if( sqlite3ExprNeedsNoAffinityChange(pRight, zStartAff[nEq]) ){
          zStartAff[nEq] = SQLITE_AFF_BLOB;
        }
      }  
      nConstraint++;
      testcase( pRangeStart->wtFlags & TERM_VIRTUAL );
    }else if( bSeekPastNull ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
      nConstraint++;
      startEq = 0;
      start_constraints = 1;
    }
    codeApplyAffinity(pParse, regBase, nConstraint - bSeekPastNull, zStartAff);
    op = aStartOp[(start_constraints<<2) + (startEq<<1) + bRev];
    assert( op!=0 );
    sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);
    VdbeCoverage(v);
    VdbeCoverageIf(v, op==OP_Rewind);  testcase( op==OP_Rewind );
    VdbeCoverageIf(v, op==OP_Last);    testcase( op==OP_Last );
    VdbeCoverageIf(v, op==OP_SeekGT);  testcase( op==OP_SeekGT );
    VdbeCoverageIf(v, op==OP_SeekGE);  testcase( op==OP_SeekGE );
    VdbeCoverageIf(v, op==OP_SeekLE);  testcase( op==OP_SeekLE );
    VdbeCoverageIf(v, op==OP_SeekLT);  testcase( op==OP_SeekLT );

    /* Load the value for the inequality constraint at the end of the
    ** range (if any).
    */
    nConstraint = nEq;
    if( pRangeEnd ){
      Expr *pRight = pRangeEnd->pExpr->pRight;
      sqlite3ExprCacheRemove(pParse, regBase+nEq, 1);
      sqlite3ExprCode(pParse, pRight, regBase+nEq);
      whereLikeOptimizationStringFixup(v, pLevel, pRangeEnd);
      if( (pRangeEnd->wtFlags & TERM_VNULL)==0
       && sqlite3ExprCanBeNull(pRight)
      ){
        sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
        VdbeCoverage(v);
      }
      if( sqlite3CompareAffinity(pRight, cEndAff)!=SQLITE_AFF_BLOB
       && !sqlite3ExprNeedsNoAffinityChange(pRight, cEndAff)
      ){
        codeApplyAffinity(pParse, regBase+nEq, 1, &cEndAff);
      }
      nConstraint++;
      testcase( pRangeEnd->wtFlags & TERM_VIRTUAL );
    }else if( bStopAtNull ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
      endEq = 0;
      nConstraint++;
    }
    sqlite3DbFree(db, zStartAff);

    /* Top of the loop body */
    pLevel->p2 = sqlite3VdbeCurrentAddr(v);

    /* Check if the index cursor is past the end of the range. */
    if( nConstraint ){
      op = aEndOp[bRev*2 + endEq];
      sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);
      testcase( op==OP_IdxGT );  VdbeCoverageIf(v, op==OP_IdxGT );
      testcase( op==OP_IdxGE );  VdbeCoverageIf(v, op==OP_IdxGE );
      testcase( op==OP_IdxLT );  VdbeCoverageIf(v, op==OP_IdxLT );
      testcase( op==OP_IdxLE );  VdbeCoverageIf(v, op==OP_IdxLE );
    }

    /* Seek the table cursor, if required */
    disableTerm(pLevel, pRangeStart);
    disableTerm(pLevel, pRangeEnd);
    if( omitTable ){
      /* pIdx is a covering index.  No need to access the main table. */
    }else if( HasRowid(pIdx->pTable) ){
      iRowidReg = ++pParse->nMem;
      sqlite3VdbeAddOp2(v, OP_IdxRowid, iIdxCur, iRowidReg);
      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
      if( pWInfo->eOnePass!=ONEPASS_OFF ){
        sqlite3VdbeAddOp3(v, OP_NotExists, iCur, 0, iRowidReg);
        VdbeCoverage(v);
      }else{
        sqlite3VdbeAddOp2(v, OP_Seek, iCur, iRowidReg);  /* Deferred seek */
      }
    }else if( iCur!=iIdxCur ){
      Index *pPk = sqlite3PrimaryKeyIndex(pIdx->pTable);
      iRowidReg = sqlite3GetTempRange(pParse, pPk->nKeyCol);
      for(j=0; j<pPk->nKeyCol; j++){
        k = sqlite3ColumnOfIndex(pIdx, pPk->aiColumn[j]);
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, k, iRowidReg+j);
      }
      sqlite3VdbeAddOp4Int(v, OP_NotFound, iCur, addrCont,
                           iRowidReg, pPk->nKeyCol); VdbeCoverage(v);
    }

    /* Record the instruction used to terminate the loop. Disable 
    ** WHERE clause terms made redundant by the index range scan.
    */
    if( pLoop->wsFlags & WHERE_ONEROW ){
      pLevel->op = OP_Noop;
    }else if( bRev ){
      pLevel->op = OP_Prev;
    }else{
      pLevel->op = OP_Next;
    }
    pLevel->p1 = iIdxCur;
    pLevel->p3 = (pLoop->wsFlags&WHERE_UNQ_WANTED)!=0 ? 1:0;
    if( (pLoop->wsFlags & WHERE_CONSTRAINT)==0 ){
      pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
    }else{
      assert( pLevel->p5==0 );
    }
  }else

#ifndef SQLITE_OMIT_OR_OPTIMIZATION
  if( pLoop->wsFlags & WHERE_MULTI_OR ){
    /* Case 5:  Two or more separately indexed terms connected by OR
    **
    ** Example:
    **
    **   CREATE TABLE t1(a,b,c,d);
    **   CREATE INDEX i1 ON t1(a);
    **   CREATE INDEX i2 ON t1(b);
    **   CREATE INDEX i3 ON t1(c);
    **
    **   SELECT * FROM t1 WHERE a=5 OR b=7 OR (c=11 AND d=13)
    **
    ** In the example, there are three indexed terms connected by OR.
    ** The top of the loop looks like this:
    **
    **          Null       1                # Zero the rowset in reg 1
    **
    ** Then, for each indexed term, the following. The arguments to
    ** RowSetTest are such that the rowid of the current row is inserted
    ** into the RowSet. If it is already present, control skips the
    ** Gosub opcode and jumps straight to the code generated by WhereEnd().
    **
    **        sqlite3WhereBegin(<term>)
    **          RowSetTest                  # Insert rowid into rowset
    **          Gosub      2 A
    **        sqlite3WhereEnd()
    **
    ** Following the above, code to terminate the loop. Label A, the target
    ** of the Gosub above, jumps to the instruction right after the Goto.
    **
    **          Null       1                # Zero the rowset in reg 1
    **          Goto       B                # The loop is finished.
    **
    **       A: <loop body>                 # Return data, whatever.
    **
    **          Return     2                # Jump back to the Gosub
    **
    **       B: <after the loop>
    **
    ** Added 2014-05-26: If the table is a WITHOUT ROWID table, then
    ** use an ephemeral index instead of a RowSet to record the primary
    ** keys of the rows we have already seen.
    **
    */
    WhereClause *pOrWc;    /* The OR-clause broken out into subterms */
    SrcList *pOrTab;       /* Shortened table list or OR-clause generation */
    Index *pCov = 0;             /* Potential covering index (or NULL) */
    int iCovCur = pParse->nTab++;  /* Cursor used for index scans (if any) */

    int regReturn = ++pParse->nMem;           /* Register used with OP_Gosub */
    int regRowset = 0;                        /* Register for RowSet object */
    int regRowid = 0;                         /* Register holding rowid */
    int iLoopBody = sqlite3VdbeMakeLabel(v);  /* Start of loop body */
    int iRetInit;                             /* Address of regReturn init */
    int untestedTerms = 0;             /* Some terms not completely tested */
    int ii;                            /* Loop counter */
    u16 wctrlFlags;                    /* Flags for sub-WHERE clause */
    Expr *pAndExpr = 0;                /* An ".. AND (...)" expression */
    Table *pTab = pTabItem->pTab;
   
    pTerm = pLoop->aLTerm[0];
    assert( pTerm!=0 );
    assert( pTerm->eOperator & WO_OR );
    assert( (pTerm->wtFlags & TERM_ORINFO)!=0 );
    pOrWc = &pTerm->u.pOrInfo->wc;
    pLevel->op = OP_Return;
    pLevel->p1 = regReturn;

    /* Set up a new SrcList in pOrTab containing the table being scanned
    ** by this loop in the a[0] slot and all notReady tables in a[1..] slots.
    ** This becomes the SrcList in the recursive call to sqlite3WhereBegin().
    */
    if( pWInfo->nLevel>1 ){
      int nNotReady;                 /* The number of notReady tables */
      struct SrcList_item *origSrc;     /* Original list of tables */
      nNotReady = pWInfo->nLevel - iLevel - 1;
      pOrTab = sqlite3StackAllocRaw(db,
                            sizeof(*pOrTab)+ nNotReady*sizeof(pOrTab->a[0]));
      if( pOrTab==0 ) return notReady;
      pOrTab->nAlloc = (u8)(nNotReady + 1);
      pOrTab->nSrc = pOrTab->nAlloc;
      memcpy(pOrTab->a, pTabItem, sizeof(*pTabItem));
      origSrc = pWInfo->pTabList->a;
      for(k=1; k<=nNotReady; k++){
        memcpy(&pOrTab->a[k], &origSrc[pLevel[k].iFrom], sizeof(pOrTab->a[k]));
      }
    }else{
      pOrTab = pWInfo->pTabList;
    }

    /* Initialize the rowset register to contain NULL. An SQL NULL is 
    ** equivalent to an empty rowset.  Or, create an ephemeral index
    ** capable of holding primary keys in the case of a WITHOUT ROWID.
    **
    ** Also initialize regReturn to contain the address of the instruction 
    ** immediately following the OP_Return at the bottom of the loop. This
    ** is required in a few obscure LEFT JOIN cases where control jumps
    ** over the top of the loop into the body of it. In this case the 
    ** correct response for the end-of-loop code (the OP_Return) is to 
    ** fall through to the next instruction, just as an OP_Next does if
    ** called on an uninitialized cursor.
    */
    if( (pWInfo->wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
      if( HasRowid(pTab) ){
        regRowset = ++pParse->nMem;
        sqlite3VdbeAddOp2(v, OP_Null, 0, regRowset);
      }else{
        Index *pPk = sqlite3PrimaryKeyIndex(pTab);
        regRowset = pParse->nTab++;
        sqlite3VdbeAddOp2(v, OP_OpenEphemeral, regRowset, pPk->nKeyCol);
        sqlite3VdbeSetP4KeyInfo(pParse, pPk);
      }
      regRowid = ++pParse->nMem;
    }
    iRetInit = sqlite3VdbeAddOp2(v, OP_Integer, 0, regReturn);

    /* If the original WHERE clause is z of the form:  (x1 OR x2 OR ...) AND y
    ** Then for every term xN, evaluate as the subexpression: xN AND z
    ** That way, terms in y that are factored into the disjunction will
    ** be picked up by the recursive calls to sqlite3WhereBegin() below.
    **
    ** Actually, each subexpression is converted to "xN AND w" where w is
    ** the "interesting" terms of z - terms that did not originate in the
    ** ON or USING clause of a LEFT JOIN, and terms that are usable as 
    ** indices.
    **
    ** This optimization also only applies if the (x1 OR x2 OR ...) term
    ** is not contained in the ON clause of a LEFT JOIN.
    ** See ticket http://www.sqlite.org/src/info/f2369304e4
    */
    if( pWC->nTerm>1 ){
      int iTerm;
      for(iTerm=0; iTerm<pWC->nTerm; iTerm++){
        Expr *pExpr = pWC->a[iTerm].pExpr;
        if( &pWC->a[iTerm] == pTerm ) continue;
        if( ExprHasProperty(pExpr, EP_FromJoin) ) continue;
        if( (pWC->a[iTerm].wtFlags & TERM_VIRTUAL)!=0 ) continue;
        if( (pWC->a[iTerm].eOperator & WO_ALL)==0 ) continue;
        testcase( pWC->a[iTerm].wtFlags & TERM_ORINFO );
        pExpr = sqlite3ExprDup(db, pExpr, 0);
        pAndExpr = sqlite3ExprAnd(db, pAndExpr, pExpr);
      }
      if( pAndExpr ){
        pAndExpr = sqlite3PExpr(pParse, TK_AND, 0, pAndExpr, 0);
      }
    }

    /* Run a separate WHERE clause for each term of the OR clause.  After
    ** eliminating duplicates from other WHERE clauses, the action for each
    ** sub-WHERE clause is to to invoke the main loop body as a subroutine.
    */
    wctrlFlags =  WHERE_OMIT_OPEN_CLOSE
                | WHERE_FORCE_TABLE
                | WHERE_ONETABLE_ONLY
                | WHERE_NO_AUTOINDEX;
    for(ii=0; ii<pOrWc->nTerm; ii++){
      WhereTerm *pOrTerm = &pOrWc->a[ii];
      if( pOrTerm->leftCursor==iCur || (pOrTerm->eOperator & WO_AND)!=0 ){
        WhereInfo *pSubWInfo;           /* Info for single OR-term scan */
        Expr *pOrExpr = pOrTerm->pExpr; /* Current OR clause term */
        int jmp1 = 0;                   /* Address of jump operation */
        if( pAndExpr && !ExprHasProperty(pOrExpr, EP_FromJoin) ){
          pAndExpr->pLeft = pOrExpr;
          pOrExpr = pAndExpr;
        }
        /* Loop through table entries that match term pOrTerm. */
        WHERETRACE(0xffff, ("Subplan for OR-clause:\n"));
        pSubWInfo = sqlite3WhereBegin(pParse, pOrTab, pOrExpr, 0, 0,
                                      wctrlFlags, iCovCur);
        assert( pSubWInfo || pParse->nErr || db->mallocFailed );
        if( pSubWInfo ){
          WhereLoop *pSubLoop;
          int addrExplain = sqlite3WhereExplainOneScan(
              pParse, pOrTab, &pSubWInfo->a[0], iLevel, pLevel->iFrom, 0
          );
          sqlite3WhereAddScanStatus(v, pOrTab, &pSubWInfo->a[0], addrExplain);

          /* This is the sub-WHERE clause body.  First skip over
          ** duplicate rows from prior sub-WHERE clauses, and record the
          ** rowid (or PRIMARY KEY) for the current row so that the same
          ** row will be skipped in subsequent sub-WHERE clauses.
          */
          if( (pWInfo->wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
            int r;
            int iSet = ((ii==pOrWc->nTerm-1)?-1:ii);
            if( HasRowid(pTab) ){
              r = sqlite3ExprCodeGetColumn(pParse, pTab, -1, iCur, regRowid, 0);
              jmp1 = sqlite3VdbeAddOp4Int(v, OP_RowSetTest, regRowset, 0,
                                           r,iSet);
              VdbeCoverage(v);
            }else{
              Index *pPk = sqlite3PrimaryKeyIndex(pTab);
              int nPk = pPk->nKeyCol;
              int iPk;

              /* Read the PK into an array of temp registers. */
              r = sqlite3GetTempRange(pParse, nPk);
              for(iPk=0; iPk<nPk; iPk++){
                int iCol = pPk->aiColumn[iPk];
                int rx;
                rx = sqlite3ExprCodeGetColumn(pParse, pTab, iCol, iCur,r+iPk,0);
                if( rx!=r+iPk ){
                  sqlite3VdbeAddOp2(v, OP_SCopy, rx, r+iPk);
                }
              }

              /* Check if the temp table already contains this key. If so,
              ** the row has already been included in the result set and
              ** can be ignored (by jumping past the Gosub below). Otherwise,
              ** insert the key into the temp table and proceed with processing
              ** the row.
              **
              ** Use some of the same optimizations as OP_RowSetTest: If iSet
              ** is zero, assume that the key cannot already be present in
              ** the temp table. And if iSet is -1, assume that there is no 
              ** need to insert the key into the temp table, as it will never 
              ** be tested for.  */ 
              if( iSet ){
                jmp1 = sqlite3VdbeAddOp4Int(v, OP_Found, regRowset, 0, r, nPk);
                VdbeCoverage(v);
              }
              if( iSet>=0 ){
                sqlite3VdbeAddOp3(v, OP_MakeRecord, r, nPk, regRowid);
                sqlite3VdbeAddOp3(v, OP_IdxInsert, regRowset, regRowid, 0);
                if( iSet ) sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
              }

              /* Release the array of temp registers */
              sqlite3ReleaseTempRange(pParse, r, nPk);
            }
          }

          /* Invoke the main loop body as a subroutine */
          sqlite3VdbeAddOp2(v, OP_Gosub, regReturn, iLoopBody);

          /* Jump here (skipping the main loop body subroutine) if the
          ** current sub-WHERE row is a duplicate from prior sub-WHEREs. */
          if( jmp1 ) sqlite3VdbeJumpHere(v, jmp1);

          /* The pSubWInfo->untestedTerms flag means that this OR term
          ** contained one or more AND term from a notReady table.  The
          ** terms from the notReady table could not be tested and will
          ** need to be tested later.
          */
          if( pSubWInfo->untestedTerms ) untestedTerms = 1;

          /* If all of the OR-connected terms are optimized using the same
          ** index, and the index is opened using the same cursor number
          ** by each call to sqlite3WhereBegin() made by this loop, it may
          ** be possible to use that index as a covering index.
          **
          ** If the call to sqlite3WhereBegin() above resulted in a scan that
          ** uses an index, and this is either the first OR-connected term
          ** processed or the index is the same as that used by all previous
          ** terms, set pCov to the candidate covering index. Otherwise, set 
          ** pCov to NULL to indicate that no candidate covering index will 
          ** be available.
          */
          pSubLoop = pSubWInfo->a[0].pWLoop;
          assert( (pSubLoop->wsFlags & WHERE_AUTO_INDEX)==0 );
          if( (pSubLoop->wsFlags & WHERE_INDEXED)!=0
           && (ii==0 || pSubLoop->u.btree.pIndex==pCov)
           && (HasRowid(pTab) || !IsPrimaryKeyIndex(pSubLoop->u.btree.pIndex))
          ){
            assert( pSubWInfo->a[0].iIdxCur==iCovCur );
            pCov = pSubLoop->u.btree.pIndex;
            wctrlFlags |= WHERE_REOPEN_IDX;
          }else{
            pCov = 0;
          }

          /* Finish the loop through table entries that match term pOrTerm. */
          sqlite3WhereEnd(pSubWInfo);
        }
      }
    }
    pLevel->u.pCovidx = pCov;
    if( pCov ) pLevel->iIdxCur = iCovCur;
    if( pAndExpr ){
      pAndExpr->pLeft = 0;
      sqlite3ExprDelete(db, pAndExpr);
    }
    sqlite3VdbeChangeP1(v, iRetInit, sqlite3VdbeCurrentAddr(v));
    sqlite3VdbeGoto(v, pLevel->addrBrk);
    sqlite3VdbeResolveLabel(v, iLoopBody);

    if( pWInfo->nLevel>1 ) sqlite3StackFree(db, pOrTab);
    if( !untestedTerms ) disableTerm(pLevel, pTerm);
  }else
#endif /* SQLITE_OMIT_OR_OPTIMIZATION */

  {
    /* Case 6:  There is no usable index.  We must do a complete
    **          scan of the entire table.
    */
    static const u8 aStep[] = { OP_Next, OP_Prev };
    static const u8 aStart[] = { OP_Rewind, OP_Last };
    assert( bRev==0 || bRev==1 );
    if( pTabItem->fg.isRecursive ){
      /* Tables marked isRecursive have only a single row that is stored in
      ** a pseudo-cursor.  No need to Rewind or Next such cursors. */
      pLevel->op = OP_Noop;
    }else{
      pLevel->op = aStep[bRev];
      pLevel->p1 = iCur;
      pLevel->p2 = 1 + sqlite3VdbeAddOp2(v, aStart[bRev], iCur, addrBrk);
      VdbeCoverageIf(v, bRev==0);
      VdbeCoverageIf(v, bRev!=0);
      pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
    }
  }