const struct platform_bind platform_keys[] = {
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_B), "A button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_Y), "X button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_SELECT), "Back button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_START), "Start button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_UP), "D-Pad Up" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_DOWN), "D-Pad Down" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_LEFT), "D-Pad Left" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_RIGHT), "D-Pad Right" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_A), "B button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_X), "Y button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_L), "Left trigger" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_R), "Right trigger" },
#if defined(_XBOX360)
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_L2), "Left shoulder" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_R2), "Right shoulder" },
#elif defined(_XBOX1)
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_L2), "Black button" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_R2), "White button" },
#endif
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_L3), "Left thumb" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_R3), "Right thumb" },
   { (1ULL << RARCH_TURBO_ENABLE), "Turbo button (Unmapped)" },
   { (1ULL << RARCH_ANALOG_LEFT_X_PLUS), "LStick Left" },
   { (1ULL << RARCH_ANALOG_LEFT_X_MINUS), "LStick Right" },
   { (1ULL << RARCH_ANALOG_LEFT_Y_PLUS), "LStick Up" },
   { (1ULL << RARCH_ANALOG_LEFT_Y_MINUS), "LStick Down" },
   { (1ULL << RARCH_ANALOG_RIGHT_X_PLUS), "RStick Left" },
   { (1ULL << RARCH_ANALOG_RIGHT_X_MINUS), "RStick Right" },
   { (1ULL << RARCH_ANALOG_RIGHT_Y_PLUS), "RStick Up" },
   { (1ULL << RARCH_ANALOG_RIGHT_Y_MINUS), "RStick Down" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_LEFT) | (1ULL << RARCH_ANALOG_LEFT_X_DPAD_LEFT), "LStick D-Pad Left" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_RIGHT) | (1ULL << RARCH_ANALOG_LEFT_X_DPAD_RIGHT), "LStick D-Pad Right" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_UP) | (1ULL << RARCH_ANALOG_LEFT_Y_DPAD_UP), "LStick D-Pad Up" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_DOWN) | (1ULL << RARCH_ANALOG_LEFT_Y_DPAD_DOWN), "LStick D-Pad Down" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_LEFT) | (1ULL << RARCH_ANALOG_RIGHT_X_DPAD_LEFT), "RStick D-Pad Left" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_RIGHT) | (1ULL << RARCH_ANALOG_RIGHT_X_DPAD_RIGHT), "RStick D-Pad Right" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_UP) | (1ULL << RARCH_ANALOG_RIGHT_Y_DPAD_UP), "RStick D-Pad Up" },
   { (1ULL << RETRO_DEVICE_ID_JOYPAD_DOWN) | (1ULL << RARCH_ANALOG_RIGHT_Y_DPAD_DOWN), "RStick D-Pad Down" },
};