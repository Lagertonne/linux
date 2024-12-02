// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode boe_nt51017_10_800p_mode = {
	.clock = (800 + 164 + 8 + 136) * (1280 + 56 + 4 + 42) * 60 / 1000,
	.hdisplay = 800,
	.hsync_start = 800 + 164,
	.hsync_end = 800 + 164 + 8,
	.htotal = 800 + 164 + 8 + 136,
	.vdisplay = 1280,
	.vsync_start = 1280 + 56,
	.vsync_end = 1280 + 56 + 4,
	.vtotal = 1280 + 56 + 4 + 42,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi boe_nt51017_10_800p = {
	.desc = {
		.modes = &boe_nt51017_10_800p_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
