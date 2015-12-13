#ifdef CONFIG_ZONE_DMA
if (dev == NULL)
		gfp |= __GFP_DMA;
	else if (dev->coherent_dma_mask <= DMA_BIT_MASK(24))
		gfp |= __GFP_DMA;
	else
#endif
#ifdef CONFIG_ZONE_DMA32
	     if (dev->coherent_dma_mask <= DMA_BIT_MASK(32))
		gfp |= __GFP_DMA32;
	else
#endif
		;