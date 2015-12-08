#ifdef S_ISCHR
if (S_ISCHR(mode)) {
		return "character device";
	} else
#endif
#ifdef S_ISBLK
	if (S_ISBLK(mode)) {
		return "block device";
	} else
#endif
#ifdef S_ISFIFO
	if (S_ISFIFO(mode)) {
		return "fifo";
	} else
#endif
#ifdef S_ISLNK
	if (S_ISLNK(mode)) {
		return "symbolic link";
	} else
#endif
#ifdef S_ISSOCK
	if (S_ISSOCK(mode)) {
		return "socket";
	} else
#endif
	return "";