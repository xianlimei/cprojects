#ifdef RAM_OFFSET
if((signed int)constmap[i+1][rs]+offset<(signed int)0x80800000) 
            emit_movimm(((constmap[i+1][rs]+offset)&0xFFFFFFF8)+(int)g_rdram-0x80000000,ra);
          else
          #endif
          emit_movimm((constmap[i+1][rs]+offset)&0xFFFFFFF8,ra);