#ifdef CONFIG_HOTPLUG_CPU
if (!setup_max_cpus)
#endif
	if (possible > i) {
		printk(KERN_WARNING
			"%d Processors exceeds max_cpus limit of %u\n",
			possible, setup_max_cpus);
		possible = i;
	}