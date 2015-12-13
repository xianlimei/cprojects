#if defined(FEATURE_WLAN_NON_INTEGRATED_SOC)
if (HAL_STATUS_SUCCESS(palWriteDeviceMemory(hHdd, memAddr, (void *)pBuf, nLen)))
#elif defined(FEATURE_WLAN_INTEGRATED_SOC)
         if (eWLAN_PAL_STATUS_SUCCESS == wpalDbgWriteMemory(memAddr, (void *)pBuf, nLen))
#endif
         {
            status = VOS_STATUS_SUCCESS;
         }
         else
         {
            status = VOS_STATUS_E_FAILURE;
         }