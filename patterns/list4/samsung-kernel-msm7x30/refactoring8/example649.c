static ctl_table xfs_table[] = {
	{
		.procname	= "irix_sgid_inherit",
		.data		= &xfs_params.sgid_inherit.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.sgid_inherit.min,
		.extra2		= &xfs_params.sgid_inherit.max
	},
	{
		.procname	= "irix_symlink_mode",
		.data		= &xfs_params.symlink_mode.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.symlink_mode.min,
		.extra2		= &xfs_params.symlink_mode.max
	},
	{
		.procname	= "panic_mask",
		.data		= &xfs_params.panic_mask.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= xfs_panic_mask_proc_handler,
		.extra1		= &xfs_params.panic_mask.min,
		.extra2		= &xfs_params.panic_mask.max
	},

	{
		.procname	= "error_level",
		.data		= &xfs_params.error_level.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.error_level.min,
		.extra2		= &xfs_params.error_level.max
	},
	{
		.procname	= "xfssyncd_centisecs",
		.data		= &xfs_params.syncd_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.syncd_timer.min,
		.extra2		= &xfs_params.syncd_timer.max
	},
	{
		.procname	= "inherit_sync",
		.data		= &xfs_params.inherit_sync.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.inherit_sync.min,
		.extra2		= &xfs_params.inherit_sync.max
	},
	{
		.procname	= "inherit_nodump",
		.data		= &xfs_params.inherit_nodump.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.inherit_nodump.min,
		.extra2		= &xfs_params.inherit_nodump.max
	},
	{
		.procname	= "inherit_noatime",
		.data		= &xfs_params.inherit_noatim.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.inherit_noatim.min,
		.extra2		= &xfs_params.inherit_noatim.max
	},
	{
		.procname	= "xfsbufd_centisecs",
		.data		= &xfs_params.xfs_buf_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.xfs_buf_timer.min,
		.extra2		= &xfs_params.xfs_buf_timer.max
	},
	{
		.procname	= "age_buffer_centisecs",
		.data		= &xfs_params.xfs_buf_age.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.xfs_buf_age.min,
		.extra2		= &xfs_params.xfs_buf_age.max
	},
	{
		.procname	= "inherit_nosymlinks",
		.data		= &xfs_params.inherit_nosym.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.inherit_nosym.min,
		.extra2		= &xfs_params.inherit_nosym.max
	},
	{
		.procname	= "rotorstep",
		.data		= &xfs_params.rotorstep.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.rotorstep.min,
		.extra2		= &xfs_params.rotorstep.max
	},
	{
		.procname	= "inherit_nodefrag",
		.data		= &xfs_params.inherit_nodfrg.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.inherit_nodfrg.min,
		.extra2		= &xfs_params.inherit_nodfrg.max
	},
	{
		.procname	= "filestream_centisecs",
		.data		= &xfs_params.fstrm_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &xfs_params.fstrm_timer.min,
		.extra2		= &xfs_params.fstrm_timer.max,
	},
	/* please keep this the last entry */
#ifdef CONFIG_PROC_FS
	{
		.procname	= "stats_clear",
		.data		= &xfs_params.stats_clear.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= xfs_stats_clear_proc_handler,
		.extra1		= &xfs_params.stats_clear.min,
		.extra2		= &xfs_params.stats_clear.max
	},
#endif /* CONFIG_PROC_FS */

	{}
};