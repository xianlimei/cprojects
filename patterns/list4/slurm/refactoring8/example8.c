static display_data_t display_data_submit[] = {
	{G_TYPE_INT, SORTID_POS, NULL, FALSE, -1},
	{G_TYPE_STRING, SORTID_PARTITION, "PARTITION", TRUE, -1},
	{G_TYPE_STRING, SORTID_AVAIL, "AVAIL", TRUE, -1},
	{G_TYPE_STRING, SORTID_TIMELIMIT, "TIMELIMIT", TRUE, -1},
	{G_TYPE_STRING, SORTID_NODES, "NODES", TRUE, -1},
#ifdef HAVE_BG
	{G_TYPE_STRING, SORTID_NODELIST, "MIDPLANELIST", TRUE, -1},
#else
	{G_TYPE_STRING, SORTID_NODELIST, "NODELIST", TRUE, -1},
#endif
	{G_TYPE_NONE, -1, NULL, FALSE, -1}
};