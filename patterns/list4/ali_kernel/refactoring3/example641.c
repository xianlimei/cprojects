switch (optname) {
	case MRT6_VERSION:
		val = 0x0305;
		break;
#ifdef CONFIG_IPV6_PIMSM_V2
	case MRT6_PIM:
		val = net->ipv6.mroute_do_pim;
		break;
#endif
	case MRT6_ASSERT:
		val = net->ipv6.mroute_do_assert;
		break;
	default:
		return -ENOPROTOOPT;
	}