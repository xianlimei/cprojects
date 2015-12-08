#ifdef YCBCR_SUPPORT
if (td->td_planarconfig == PLANARCONFIG_CONTIG &&
	    td->td_photometric == PHOTOMETRIC_YCBCR &&
	    !isUpSampled(tif)) {
		/*
		 * Packed YCbCr data contain one Cb+Cr for every
		 * HorizontalSampling*VerticalSampling Y values.
		 * Must also roundup width and height when calculating
		 * since images that are not a multiple of the
		 * horizontal/vertical subsampling area include
		 * YCbCr data for the extended image.
		 */
		tsize_t w =
		    TIFFroundup(td->td_imagewidth, td->td_ycbcrsubsampling[0]);
		tsize_t scanline = TIFFhowmany(w*td->td_bitspersample, 8);
		tsize_t samplingarea =
		    td->td_ycbcrsubsampling[0]*td->td_ycbcrsubsampling[1];
		nrows = TIFFroundup(nrows, td->td_ycbcrsubsampling[1]);
		/* NB: don't need TIFFhowmany here 'cuz everything is rounded */
		return ((tsize_t)
		    (nrows*scanline + 2*(nrows*scanline / samplingarea)));
	} else
#endif
		return ((tsize_t)(nrows * TIFFScanlineSize(tif)));