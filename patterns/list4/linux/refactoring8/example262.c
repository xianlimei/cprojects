static const uint32_t ehci_hdr[] = {  /* dev f function 4 - devfn = 7d */
	0xfffff000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20951022, 0x2300006, 0xc032002, 0x0,
	0xfe01b000, 0x0, 0x0,	0x0,			/* MEMBAR-1000 */
	0x0,	0x0,	0x0,	0x20951022,
	0x0,	0x40,	0x0,	0x40a,			/* CapPtr INT-D, IRQA */
	0xc8020001, 0x0, 0x0,	0x0,	/* Capabilities - 40 is R/O, 44 is
					   mask 8103 (power control) */
#if 0
	0x1,	0x40080000, 0x0, 0x0,	/* EECP - see EHCI spec section 2.1.7 */
#endif
	0x01000001, 0x0, 0x0,	0x0,	/* EECP - see EHCI spec section 2.1.7 */
	0x2020,	0x0,	0x0,	0x0,	/* (EHCI page 8) 60 SBRN (R/O),
					   61 FLADJ (R/W), PORTWAKECAP  */
};