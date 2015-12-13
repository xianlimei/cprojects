static int call_lvds_manufacturer_script(struct drm_device *dev, struct dcb_output *dcbent, int head, enum LVDS_script script)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	uint8_t sub = bios->data[bios->fp.xlated_entry + script] + (bios->fp.link_c_increment && dcbent->or & DCB_OUTPUT_C ? 1 : 0);
	uint16_t scriptofs = ROM16(bios->data[bios->init_script_tbls_ptr + sub * 2]);

	if (!bios->fp.xlated_entry || !sub || !scriptofs)
		return -EINVAL;

	run_digital_op_script(dev, scriptofs, dcbent, head, bios->fp.dual_link);

	if (script == LVDS_PANEL_OFF) {
		/* off-on delay in ms */
		mdelay(ROM16(bios->data[bios->fp.xlated_entry + 7]));
	}
#ifdef __powerpc__
	/* Powerbook specific quirks */
	if (script == LVDS_RESET &&
	    (dev->pdev->device == 0x0179 || dev->pdev->device == 0x0189 ||
	     dev->pdev->device == 0x0329))
		nv_write_tmds(dev, dcbent->or, 0, 0x02, 0x72);
#endif

	return 0;
}