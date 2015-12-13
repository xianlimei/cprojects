static struct resource realview_pb1176_flash_resources[] = {
	{
		.start		= REALVIEW_PB1176_FLASH_BASE,
		.end		= REALVIEW_PB1176_FLASH_BASE + REALVIEW_PB1176_FLASH_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
#ifdef CONFIG_REALVIEW_PB1176_SECURE_FLASH
	{
		.start		= REALVIEW_PB1176_SEC_FLASH_BASE,
		.end		= REALVIEW_PB1176_SEC_FLASH_BASE + REALVIEW_PB1176_SEC_FLASH_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
#endif
};