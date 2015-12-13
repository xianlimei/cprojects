#ifdef CONFIG_BAND_CBAND
if (state->current_band == BAND_CBAND && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		} else
#endif
		if ((state->current_band == BAND_CBAND || state->current_band == BAND_VHF) && state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband_7090p);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal_socs);
		} else {
			dib0090_set_rframp(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		}