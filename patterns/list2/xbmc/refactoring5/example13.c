#ifdef MNG_INCLUDE_JNG
if (((mng_datap)hHandle)->eImagetype == mng_it_jng)
    iRslt = ((mng_datap)hHandle)->iJHDRalphafilter;
  else
#endif
    iRslt = 0;