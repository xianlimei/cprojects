static ctl_table xfs_table[] = {
	{
		.ctl_name	= XFS_SGID_INHERIT,
		.procname	= "irix_sgid_inherit",
		.data		= &xfs_params.sgid_inherit.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.sgid_inherit.min,
		.extra2		= &xfs_params.sgid_inherit.max
	},
	{
		.ctl_name	= XFS_SYMLINK_MODE,
		.procname	= "irix_symlink_mode",
		.data		= &xfs_params.symlink_mode.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.symlink_mode.min,
		.extra2		= &xfs_params.symlink_mode.max
	},
	{
		.ctl_name	= XFS_PANIC_MASK,
		.procname	= "panic_mask",
		.data		= &xfs_params.panic_mask.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= xfs_panic_mask_proc_handler,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.panic_mask.min,
		.extra2		= &xfs_params.panic_mask.max
	},

	{
		.ctl_name	= XFS_ERRLEVEL,
		.procname	= "error_level",
		.data		= &xfs_params.error_level.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.error_level.min,
		.extra2		= &xfs_params.error_level.max
	},
	{
		.ctl_name	= XFS_SYNCD_TIMER,
		.procname	= "xfssyncd_centisecs",
		.data		= &xfs_params.syncd_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.syncd_timer.min,
		.extra2		= &xfs_params.syncd_timer.max
	},
	{
		.ctl_name	= XFS_INHERIT_SYNC,
		.procname	= "inherit_sync",
		.data		= &xfs_params.inherit_sync.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.inherit_sync.min,
		.extra2		= &xfs_params.inherit_sync.max
	},
	{
		.ctl_name	= XFS_INHERIT_NODUMP,
		.procname	= "inherit_nodump",
		.data		= &xfs_params.inherit_nodump.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.inherit_nodump.min,
		.extra2		= &xfs_params.inherit_nodump.max
	},
	{
		.ctl_name	= XFS_INHERIT_NOATIME,
		.procname	= "inherit_noatime",
		.data		= &xfs_params.inherit_noatim.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.inherit_noatim.min,
		.extra2		= &xfs_params.inherit_noatim.max
	},
	{
		.ctl_name	= XFS_BUF_TIMER,
		.procname	= "xfsbufd_centisecs",
		.data		= &xfs_params.xfs_buf_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.xfs_buf_timer.min,
		.extra2		= &xfs_params.xfs_buf_timer.max
	},
	{
		.ctl_name	= XFS_BUF_AGE,
		.procname	= "age_buffer_centisecs",
		.data		= &xfs_params.xfs_buf_age.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.xfs_buf_age.min,
		.extra2		= &xfs_params.xfs_buf_age.max
	},
	{
		.ctl_name	= XFS_INHERIT_NOSYM,
		.procname	= "inherit_nosymlinks",
		.data		= &xfs_params.inherit_nosym.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.inherit_nosym.min,
		.extra2		= &xfs_params.inherit_nosym.max
	},
	{
		.ctl_name	= XFS_ROTORSTEP,
		.procname	= "rotorstep",
		.data		= &xfs_params.rotorstep.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.rotorstep.min,
		.extra2		= &xfs_params.rotorstep.max
	},
	{
		.ctl_name	= XFS_INHERIT_NODFRG,
		.procname	= "inherit_nodefrag",
		.data		= &xfs_params.inherit_nodfrg.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.inherit_nodfrg.min,
		.extra2		= &xfs_params.inherit_nodfrg.max
	},
	{
		.ctl_name	= XFS_FILESTREAM_TIMER,
		.procname	= "filestream_centisecs",
		.data		= &xfs_params.fstrm_timer.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &proc_dointvec_minmax,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.fstrm_timer.min,
		.extra2		= &xfs_params.fstrm_timer.max,
	},
	/* please keep this the last entry */
#ifdef CONFIG_PROC_FS
	{
		.ctl_name	= XFS_STATS_CLEAR,
		.procname	= "stats_clear",
		.data		= &xfs_params.stats_clear.val,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= &xfs_stats_clear_proc_handler,
		.strategy	= &sysctl_intvec,
		.extra1		= &xfs_params.stats_clear.min,
		.extra2		= &xfs_params.stats_clear.max
	},
#endif /* CONFIG_PROC_FS */

	{}
};