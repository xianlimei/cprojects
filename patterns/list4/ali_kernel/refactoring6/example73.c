if (
#ifdef USE_FBR0
	    (ri == 0 && bi < rx_local->Fbr0NumEntries) ||
#endif
	    (ri == 1 && bi < rx_local->Fbr1NumEntries)) {
		spin_lock_irqsave(&etdev->FbrLock, flags);

		if (ri == 1) {
			PFBR_DESC_t pNextDesc =
			    (PFBR_DESC_t) (rx_local->pFbr1RingVa) +
			    INDEX10(rx_local->local_Fbr1_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed)FBR entry
			 */
			pNextDesc->addr_hi = rx_local->Fbr[1]->PAHigh[bi];
			pNextDesc->addr_lo = rx_local->Fbr[1]->PALow[bi];
			pNextDesc->word2.value = bi;

			writel(bump_fbr(&rx_local->local_Fbr1_full,
				rx_local->Fbr1NumEntries - 1),
				&rx_dma->fbr1_full_offset);
		}
#ifdef USE_FBR0
		else {
			PFBR_DESC_t pNextDesc =
			    (PFBR_DESC_t) rx_local->pFbr0RingVa +
			    INDEX10(rx_local->local_Fbr0_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed) FBR entry
			 */
			pNextDesc->addr_hi = rx_local->Fbr[0]->PAHigh[bi];
			pNextDesc->addr_lo = rx_local->Fbr[0]->PALow[bi];
			pNextDesc->word2.value = bi;

			writel(bump_fbr(&rx_local->local_Fbr0_full,
					rx_local->Fbr0NumEntries - 1),
			       &rx_dma->fbr0_full_offset);
		}
#endif
		spin_unlock_irqrestore(&etdev->FbrLock, flags);
	} else {
		dev_err(&etdev->pdev->dev,
			  "NICReturnRFD illegal Buffer Index returned\n");
	}