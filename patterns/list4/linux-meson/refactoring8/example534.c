static const unsigned short ppi_req[] = {
	P_PPI0_D0, P_PPI0_D1, P_PPI0_D2, P_PPI0_D3,
	P_PPI0_D4, P_PPI0_D5, P_PPI0_D6, P_PPI0_D7,
	P_PPI0_D8, P_PPI0_D9, P_PPI0_D10, P_PPI0_D11,
	P_PPI0_D12, P_PPI0_D13, P_PPI0_D14, P_PPI0_D15,
#if !defined(CONFIG_VIDEO_VS6624) && !defined(CONFIG_VIDEO_VS6624_MODULE)
	P_PPI0_D16, P_PPI0_D17, P_PPI0_D18, P_PPI0_D19,
	P_PPI0_D20, P_PPI0_D21, P_PPI0_D22, P_PPI0_D23,
#endif
	P_PPI0_CLK, P_PPI0_FS1, P_PPI0_FS2,
	0,
};