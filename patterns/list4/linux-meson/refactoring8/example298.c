static struct insn opcode_b3[] = {
#ifdef CONFIG_64BIT
	{ "maylr", 0x38, INSTR_RRF_F0FF },
	{ "mylr", 0x39, INSTR_RRF_F0FF },
	{ "mayr", 0x3a, INSTR_RRF_F0FF },
	{ "myr", 0x3b, INSTR_RRF_F0FF },
	{ "mayhr", 0x3c, INSTR_RRF_F0FF },
	{ "myhr", 0x3d, INSTR_RRF_F0FF },
	{ "lpdfr", 0x70, INSTR_RRE_FF },
	{ "lndfr", 0x71, INSTR_RRE_FF },
	{ "cpsdr", 0x72, INSTR_RRF_F0FF2 },
	{ "lcdfr", 0x73, INSTR_RRE_FF },
	{ "sfasr", 0x85, INSTR_RRE_R0 },
	{ { 0, LONG_INSN_CELFBR }, 0x90, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CDLFBR }, 0x91, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CXLFBR }, 0x92, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CEFBRA }, 0x94, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CDFBRA }, 0x95, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CXFBRA }, 0x96, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CFEBRA }, 0x98, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CFDBRA }, 0x99, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CFXBRA }, 0x9a, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CLFEBR }, 0x9c, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CLFDBR }, 0x9d, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CLFXBR }, 0x9e, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CELGBR }, 0xa0, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CDLGBR }, 0xa1, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CXLGBR }, 0xa2, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CEGBRA }, 0xa4, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CDGBRA }, 0xa5, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CXGBRA }, 0xa6, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CGEBRA }, 0xa8, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CGDBRA }, 0xa9, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CGXBRA }, 0xaa, INSTR_RRF_UUFR },
	{ { 0, LONG_INSN_CLGEBR }, 0xac, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CLGDBR }, 0xad, INSTR_RRF_UURF },
	{ { 0, LONG_INSN_CLGXBR }, 0xae, INSTR_RRF_UUFR },
	{ "ldgr", 0xc1, INSTR_RRE_FR },
	{ "cegr", 0xc4, INSTR_RRE_FR },
	{ "cdgr", 0xc5, INSTR_RRE_FR },
	{ "cxgr", 0xc6, INSTR_RRE_FR },
	{ "cger", 0xc8, INSTR_RRF_U0RF },
	{ "cgdr", 0xc9, INSTR_RRF_U0RF },
	{ "cgxr", 0xca, INSTR_RRF_U0RF },
	{ "lgdr", 0xcd, INSTR_RRE_RF },
	{ "mdtra", 0xd0, INSTR_RRF_FUFF2 },
	{ "ddtra", 0xd1, INSTR_RRF_FUFF2 },
	{ "adtra", 0xd2, INSTR_RRF_FUFF2 },
	{ "sdtra", 0xd3, INSTR_RRF_FUFF2 },
	{ "ldetr", 0xd4, INSTR_RRF_0UFF },
	{ "ledtr", 0xd5, INSTR_RRF_UUFF },
	{ "ltdtr", 0xd6, INSTR_RRE_FF },
	{ "fidtr", 0xd7, INSTR_RRF_UUFF },
	{ "mxtra", 0xd8, INSTR_RRF_FUFF2 },
	{ "dxtra", 0xd9, INSTR_RRF_FUFF2 },
	{ "axtra", 0xda, INSTR_RRF_FUFF2 },
	{ "sxtra", 0xdb, INSTR_RRF_FUFF2 },
	{ "lxdtr", 0xdc, INSTR_RRF_0UFF },
	{ "ldxtr", 0xdd, INSTR_RRF_UUFF },
	{ "ltxtr", 0xde, INSTR_RRE_FF },
	{ "fixtr", 0xdf, INSTR_RRF_UUFF },
	{ "kdtr", 0xe0, INSTR_RRE_FF },
	{ { 0, LONG_INSN_CGDTRA }, 0xe1, INSTR_RRF_UURF },
	{ "cudtr", 0xe2, INSTR_RRE_RF },
	{ "csdtr", 0xe3, INSTR_RRE_RF },
	{ "cdtr", 0xe4, INSTR_RRE_FF },
	{ "eedtr", 0xe5, INSTR_RRE_RF },
	{ "esdtr", 0xe7, INSTR_RRE_RF },
	{ "kxtr", 0xe8, INSTR_RRE_FF },
	{ { 0, LONG_INSN_CGXTRA }, 0xe9, INSTR_RRF_UUFR },
	{ "cuxtr", 0xea, INSTR_RRE_RF },
	{ "csxtr", 0xeb, INSTR_RRE_RF },
	{ "cxtr", 0xec, INSTR_RRE_FF },
	{ "eextr", 0xed, INSTR_RRE_RF },
	{ "esxtr", 0xef, INSTR_RRE_RF },
	{ { 0, LONG_INSN_CDGTRA }, 0xf1, INSTR_RRF_UUFR },
	{ "cdutr", 0xf2, INSTR_RRE_FR },
	{ "cdstr", 0xf3, INSTR_RRE_FR },
	{ "cedtr", 0xf4, INSTR_RRE_FF },
	{ "qadtr", 0xf5, INSTR_RRF_FUFF },
	{ "iedtr", 0xf6, INSTR_RRF_F0FR },
	{ "rrdtr", 0xf7, INSTR_RRF_FFRU },
	{ { 0, LONG_INSN_CXGTRA }, 0xf9, INSTR_RRF_UURF },
	{ "cxutr", 0xfa, INSTR_RRE_FR },
	{ "cxstr", 0xfb, INSTR_RRE_FR },
	{ "cextr", 0xfc, INSTR_RRE_FF },
	{ "qaxtr", 0xfd, INSTR_RRF_FUFF },
	{ "iextr", 0xfe, INSTR_RRF_F0FR },
	{ "rrxtr", 0xff, INSTR_RRF_FFRU },
#endif
	{ "lpebr", 0x00, INSTR_RRE_FF },
	{ "lnebr", 0x01, INSTR_RRE_FF },
	{ "ltebr", 0x02, INSTR_RRE_FF },
	{ "lcebr", 0x03, INSTR_RRE_FF },
	{ "ldebr", 0x04, INSTR_RRE_FF },
	{ "lxdbr", 0x05, INSTR_RRE_FF },
	{ "lxebr", 0x06, INSTR_RRE_FF },
	{ "mxdbr", 0x07, INSTR_RRE_FF },
	{ "kebr", 0x08, INSTR_RRE_FF },
	{ "cebr", 0x09, INSTR_RRE_FF },
	{ "aebr", 0x0a, INSTR_RRE_FF },
	{ "sebr", 0x0b, INSTR_RRE_FF },
	{ "mdebr", 0x0c, INSTR_RRE_FF },
	{ "debr", 0x0d, INSTR_RRE_FF },
	{ "maebr", 0x0e, INSTR_RRF_F0FF },
	{ "msebr", 0x0f, INSTR_RRF_F0FF },
	{ "lpdbr", 0x10, INSTR_RRE_FF },
	{ "lndbr", 0x11, INSTR_RRE_FF },
	{ "ltdbr", 0x12, INSTR_RRE_FF },
	{ "lcdbr", 0x13, INSTR_RRE_FF },
	{ "sqebr", 0x14, INSTR_RRE_FF },
	{ "sqdbr", 0x15, INSTR_RRE_FF },
	{ "sqxbr", 0x16, INSTR_RRE_FF },
	{ "meebr", 0x17, INSTR_RRE_FF },
	{ "kdbr", 0x18, INSTR_RRE_FF },
	{ "cdbr", 0x19, INSTR_RRE_FF },
	{ "adbr", 0x1a, INSTR_RRE_FF },
	{ "sdbr", 0x1b, INSTR_RRE_FF },
	{ "mdbr", 0x1c, INSTR_RRE_FF },
	{ "ddbr", 0x1d, INSTR_RRE_FF },
	{ "madbr", 0x1e, INSTR_RRF_F0FF },
	{ "msdbr", 0x1f, INSTR_RRF_F0FF },
	{ "lder", 0x24, INSTR_RRE_FF },
	{ "lxdr", 0x25, INSTR_RRE_FF },
	{ "lxer", 0x26, INSTR_RRE_FF },
	{ "maer", 0x2e, INSTR_RRF_F0FF },
	{ "mser", 0x2f, INSTR_RRF_F0FF },
	{ "sqxr", 0x36, INSTR_RRE_FF },
	{ "meer", 0x37, INSTR_RRE_FF },
	{ "madr", 0x3e, INSTR_RRF_F0FF },
	{ "msdr", 0x3f, INSTR_RRF_F0FF },
	{ "lpxbr", 0x40, INSTR_RRE_FF },
	{ "lnxbr", 0x41, INSTR_RRE_FF },
	{ "ltxbr", 0x42, INSTR_RRE_FF },
	{ "lcxbr", 0x43, INSTR_RRE_FF },
	{ { 0, LONG_INSN_LEDBRA }, 0x44, INSTR_RRF_UUFF },
	{ { 0, LONG_INSN_LDXBRA }, 0x45, INSTR_RRF_UUFF },
	{ { 0, LONG_INSN_LEXBRA }, 0x46, INSTR_RRF_UUFF },
	{ { 0, LONG_INSN_FIXBRA }, 0x47, INSTR_RRF_UUFF },
	{ "kxbr", 0x48, INSTR_RRE_FF },
	{ "cxbr", 0x49, INSTR_RRE_FF },
	{ "axbr", 0x4a, INSTR_RRE_FF },
	{ "sxbr", 0x4b, INSTR_RRE_FF },
	{ "mxbr", 0x4c, INSTR_RRE_FF },
	{ "dxbr", 0x4d, INSTR_RRE_FF },
	{ "tbedr", 0x50, INSTR_RRF_U0FF },
	{ "tbdr", 0x51, INSTR_RRF_U0FF },
	{ "diebr", 0x53, INSTR_RRF_FUFF },
	{ { 0, LONG_INSN_FIEBRA }, 0x57, INSTR_RRF_UUFF },
	{ "thder", 0x58, INSTR_RRE_FF },
	{ "thdr", 0x59, INSTR_RRE_FF },
	{ "didbr", 0x5b, INSTR_RRF_FUFF },
	{ { 0, LONG_INSN_FIDBRA }, 0x5f, INSTR_RRF_UUFF },
	{ "lpxr", 0x60, INSTR_RRE_FF },
	{ "lnxr", 0x61, INSTR_RRE_FF },
	{ "ltxr", 0x62, INSTR_RRE_FF },
	{ "lcxr", 0x63, INSTR_RRE_FF },
	{ "lxr", 0x65, INSTR_RRE_FF },
	{ "lexr", 0x66, INSTR_RRE_FF },
	{ "fixr", 0x67, INSTR_RRE_FF },
	{ "cxr", 0x69, INSTR_RRE_FF },
	{ "lzer", 0x74, INSTR_RRE_F0 },
	{ "lzdr", 0x75, INSTR_RRE_F0 },
	{ "lzxr", 0x76, INSTR_RRE_F0 },
	{ "fier", 0x77, INSTR_RRE_FF },
	{ "fidr", 0x7f, INSTR_RRE_FF },
	{ "sfpc", 0x84, INSTR_RRE_RR_OPT },
	{ "efpc", 0x8c, INSTR_RRE_RR_OPT },
	{ "cefbr", 0x94, INSTR_RRE_RF },
	{ "cdfbr", 0x95, INSTR_RRE_RF },
	{ "cxfbr", 0x96, INSTR_RRE_RF },
	{ "cfebr", 0x98, INSTR_RRF_U0RF },
	{ "cfdbr", 0x99, INSTR_RRF_U0RF },
	{ "cfxbr", 0x9a, INSTR_RRF_U0RF },
	{ "cefr", 0xb4, INSTR_RRE_FR },
	{ "cdfr", 0xb5, INSTR_RRE_FR },
	{ "cxfr", 0xb6, INSTR_RRE_FR },
	{ "cfer", 0xb8, INSTR_RRF_U0RF },
	{ "cfdr", 0xb9, INSTR_RRF_U0RF },
	{ "cfxr", 0xba, INSTR_RRF_U0RF },
	{ "", 0, INSTR_INVALID }
};