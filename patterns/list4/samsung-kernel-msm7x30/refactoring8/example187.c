static int const bat_iter[] = {
	SLOT_STATUS, VOLTAGE, CURRENT, CAPACITY_REMAINING,
#ifdef EC_FULL_DIAG
	AVERAGE_CURRENT, TEMPERATURE, TIME_REMAINING,
#endif
};