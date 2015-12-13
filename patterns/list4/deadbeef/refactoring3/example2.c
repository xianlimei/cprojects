switch(info->EMU_CORE)
	{
#ifdef ENABLE_ALL_CORES
	case EC_MAME:
		ay8910_update_one(info->chip, outputs, samples);
		break;
#endif
	case EC_EMU2149:
		PSG_calc_stereo((PSG*)info->chip, outputs, samples);
		break;
	}