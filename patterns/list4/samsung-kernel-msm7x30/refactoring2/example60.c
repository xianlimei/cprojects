#ifdef WLAN_FEATURE_P2P
if((pMac->lim.gLimHalScanState != eLIM_HAL_SCANNING_STATE) || (NULL == pMac->lim.gpLimMlmScanReq) 
               || !pMac->lim.gpLimMlmScanReq->p2pSearch )
#endif
            {
                limCheckAndAddBssDescription(pMac, pBeacon, pRxPacketInfo, 
                       ((pMac->lim.gLimHalScanState == eLIM_HAL_SCANNING_STATE) ? eANI_BOOLEAN_TRUE : eANI_BOOLEAN_FALSE), 
                       eANI_BOOLEAN_FALSE);
            }