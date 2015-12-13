static unsigned int vpu_clk_setting[][3] = {
	//frequency		clk_mux		div
	{106250000,		1,			7},	//0
	{127500000,		2,			3},	//1
	{159375000,		0,			3},	//2
	{212500000,		1,			3},	//3
	{255000000,		2,			1},	//4
	{283333000,		1,			2},	//5
	{318750000,		0,			1},	//6
	{425000000,		1,			1},	//7
	{510000000,		2,			0},	//8
	{637500000,		0,			0},	//9
#ifdef GP1_CLK_TEST
	{696000000,		7,			0},	//10
	{850000000,		1,			0},	//11
#else
	{850000000,		1,			0},	//10
#endif
};