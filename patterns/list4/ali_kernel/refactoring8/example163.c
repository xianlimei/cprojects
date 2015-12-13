static unsigned long cs_phys[] = {
#ifdef CONFIG_ARCH_SA1100
	SA1100_CS0_PHYS,
	SA1100_CS1_PHYS,
	SA1100_CS2_PHYS,
	SA1100_CS3_PHYS,
	SA1100_CS4_PHYS,
	SA1100_CS5_PHYS,
#else
	PXA_CS0_PHYS,
	PXA_CS1_PHYS,
	PXA_CS2_PHYS,
	PXA_CS3_PHYS,
	PXA_CS4_PHYS,
	PXA_CS5_PHYS,
#endif
};