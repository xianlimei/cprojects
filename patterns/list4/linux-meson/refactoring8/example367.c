static struct intc_vect vectors[] __initdata = {
	/* IRQ0->5 are handled in setup-sh3.c */
	INTC_VECT(DMAC1, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC1, 0x840), INTC_VECT(DMAC1, 0x860),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8c0), INTC_VECT(SCIF0, 0x8e0),
	INTC_VECT(SCIF1, 0x900), INTC_VECT(SCIF1, 0x920),
	INTC_VECT(SCIF1, 0x940), INTC_VECT(SCIF1, 0x960),
	INTC_VECT(DMAC2, 0xb80), INTC_VECT(DMAC2, 0xba0),
#ifdef CONFIG_CPU_SUBTYPE_SH7710
	INTC_VECT(IPSEC, 0xbe0),
#endif
	INTC_VECT(EDMAC0, 0xc00), INTC_VECT(EDMAC1, 0xc20),
	INTC_VECT(EDMAC2, 0xc40),
	INTC_VECT(SIOF0, 0xe00), INTC_VECT(SIOF0, 0xe20),
	INTC_VECT(SIOF0, 0xe40), INTC_VECT(SIOF0, 0xe60),
	INTC_VECT(SIOF1, 0xe80), INTC_VECT(SIOF1, 0xea0),
	INTC_VECT(SIOF1, 0xec0), INTC_VECT(SIOF1, 0xee0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF, 0x580),
};