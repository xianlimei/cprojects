switch(rsrc->compression) {
	case 0:  /* No compression. */
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
#endif
		break;
	default: /* Unsupported compression. */
		/* Return a warning. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported ZIP compression method (%s)",
		    compression_name(rsrc->compression));
		/* We can't decompress this entry, but we will
		 * be able to skip() it and try the next entry. */
		return (ARCHIVE_WARN);
	}