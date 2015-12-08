switch( next & 0x07 ) {
		case JUDY_1:
		case JUDY_2:
		case JUDY_4:
		case JUDY_8:
		case JUDY_16:
		case JUDY_32:
#ifdef ASKITIS
		case JUDY_64:
#endif
			keysize = JUDY_key_size - (off & JUDY_key_mask);
			node = (JudySlot *)((next & JUDY_mask) + size);
			base = (uchar *)(next & JUDY_mask);
			cnt = size / (sizeof(JudySlot) + keysize);

			for( slot = 0; slot < cnt; slot++ )
				if( node[-slot-1] )
					break;

			judy->stack[judy->level].slot = slot;
#if BYTE_ORDER != BIG_ENDIAN
			if( !judy->depth && !base[slot * keysize] || judy->depth && ++depth == judy->depth )
				return &node[-slot-1];
#else
			if( !judy->depth && !base[slot * keysize + keysize - 1] || judy->depth && ++depth == judy->depth )
				return &node[-slot-1];
#endif
			next = node[-slot - 1];
			off = (off | JUDY_key_mask) + 1;
			continue;
		case JUDY_radix:
			off++;

			if( judy->depth )
			  if( !(off & JUDY_key_mask) )
				depth++;

			table = (JudySlot *)(next & JUDY_mask);
			for( slot = 0; slot < 256; slot++ )
			  if( (inner = (JudySlot *)(table[slot >> 4] & JUDY_mask)) ) {
				if( (next = inner[slot & 0x0F]) ) {
				  judy->stack[judy->level].slot = slot;
				  if( !judy->depth && !slot || judy->depth && depth == judy->depth )
					return &inner[slot & 0x0F];
				  else
					break;
				}
			  } else
				slot |= 0x0F;
			continue;
#ifndef ASKITIS
		case JUDY_span:
			node = (JudySlot *)((next & JUDY_mask) + JudySize[JUDY_span]);
			base = (uchar *)(next & JUDY_mask);
			cnt = JUDY_span_bytes;
			if( !base[cnt - 1] )	// leaf node?
				return &node[-1];
			next = node[-1];
			off += cnt;
			continue;
#endif
		}