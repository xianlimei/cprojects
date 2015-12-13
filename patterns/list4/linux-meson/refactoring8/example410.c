static struct map_desc emev2_io_desc[] __initdata = {
#ifdef CONFIG_SMP
	/* 128K entity map for 0xe0100000 (SMU) */
	{
		.virtual	= 0xe0100000,
		.pfn		= __phys_to_pfn(0xe0100000),
		.length		= SZ_128K,
		.type		= MT_DEVICE
	},
	/* 2M mapping for SCU + L2 controller */
	{
		.virtual	= 0xf0000000,
		.pfn		= __phys_to_pfn(0x1e000000),
		.length		= SZ_2M,
		.type		= MT_DEVICE
	},
#endif
};