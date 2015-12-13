switch (cmd) {
#ifdef AVMB1_COMPAT
	case AVMB1_LOAD:
	case AVMB1_LOAD_AND_CONFIG:
	case AVMB1_RESETCARD:
	case AVMB1_GET_CARDINFO:
	case AVMB1_REMOVECARD:
		return old_capi_manufacturer(cmd, data);
#endif
	case KCAPI_CMD_TRACE:
	{
		kcapi_flagdef fdef;

		if (copy_from_user(&fdef, data, sizeof(kcapi_flagdef)))
			return -EFAULT;

		card = get_capi_ctr_by_nr(fdef.contr);
		if (!card)
			return -ESRCH;

		card->traceflag = fdef.flag;
		printk(KERN_INFO "kcapi: contr [%03d] set trace=%d\n",
			card->cnr, card->traceflag);
		return 0;
	}
	case KCAPI_CMD_ADDCARD:
	{
		struct list_head *l;
		struct capi_driver *driver = NULL;
		capicardparams cparams;
		kcapi_carddef cdef;
		int retval;

		if ((retval = copy_from_user(&cdef, data, sizeof(cdef))))
			return retval;

		cparams.port = cdef.port;
		cparams.irq = cdef.irq;
		cparams.membase = cdef.membase;
		cparams.cardnr = cdef.cardnr;
		cparams.cardtype = 0;
		cdef.driver[sizeof(cdef.driver)-1] = 0;

		list_for_each(l, &capi_drivers) {
			driver = list_entry(l, struct capi_driver, list);
			if (strcmp(driver->name, cdef.driver) == 0)
				break;
		}
		if (driver == NULL) {
			printk(KERN_ERR "kcapi: driver \"%s\" not loaded.\n",
					cdef.driver);
			return -ESRCH;
		}

		if (!driver->add_card) {
			printk(KERN_ERR "kcapi: driver \"%s\" has no add card function.\n", cdef.driver);
			return -EIO;
		}

		return driver->add_card(driver, &cparams);
	}

	default:
		printk(KERN_ERR "kcapi: manufacturer command %d unknown.\n",
					cmd);
		break;

	}