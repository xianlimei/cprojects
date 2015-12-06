const char *long_fmt[] = {
		"foo|%0123ld|bar",
#if !OS_IRIX
		"% '0123ld",
		"%+'0123ld",
		"%-'123ld",
		"%'123ld",
#endif	/* !OS_IRiX */
		"%123.9ld",
		"% 123.9ld",
		"%+123.9ld",
		"%-123.9ld",
		"%0123ld",
		"% 0123ld",
		"%+0123ld",
		"%-0123ld",
		"%10.5ld",
		"% 10.5ld",
		"%+10.5ld",
		"%-10.5ld",
		"%010ld",
		"% 010ld",
		"%+010ld",
		"%-010ld",
		"%4.2ld",
		"% 4.2ld",
		"%+4.2ld",
		"%-4.2ld",
		"%04ld",
		"% 04ld",
		"%+04ld",
		"%-04ld",
		"%5.5ld",
		"%+22.33ld",
		"%01.3ld",
		"%1.5ld",
		"%-1.5ld",
		"%44ld",
		"%4ld",
		"%4.0ld",
		"%4.ld",
		"%.44ld",
		"%.4ld",
		"%.0ld",
		"%.ld",
		"%ld",
		NULL
	};
