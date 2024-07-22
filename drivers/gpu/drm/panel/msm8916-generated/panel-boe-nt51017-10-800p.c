// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2023 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct boe_nt51017_10_800p {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct boe_nt51017_10_800p *to_boe_nt51017_10_800p(struct drm_panel *panel)
{
	return container_of(panel, struct boe_nt51017_10_800p, panel);
}

static void boe_nt51017_10_800p_reset(struct boe_nt51017_10_800p *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(120);
}

static int boe_nt51017_10_800p_on(struct boe_nt51017_10_800p *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	pr_warn("Start _on for BOE NT51017_10_800p");

	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x96);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x69);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x91, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0x92, 0x57);
	mipi_dsi_dcs_write_seq(dsi, 0x93, 0x20);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_READ_PPS_CONTINUE, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0xaa, 0xfa);
	mipi_dsi_dcs_write_seq(dsi, 0xab, 0xf3);
	mipi_dsi_dcs_write_seq(dsi, 0xac, 0xed);
	mipi_dsi_dcs_write_seq(dsi, 0xad, 0xe7);
	mipi_dsi_dcs_write_seq(dsi, 0xae, 0xe2);
	mipi_dsi_dcs_write_seq(dsi, 0xaf, 0xdc);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0xd7);
	mipi_dsi_dcs_write_seq(dsi, 0xb1, 0xd1);
	mipi_dsi_dcs_write_seq(dsi, 0xb2, 0xcc);
	mipi_dsi_dcs_write_seq(dsi, 0x99, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xf5, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x96, 0x40);

	return 0;
}

static int boe_nt51017_10_800p_off(struct boe_nt51017_10_800p *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;

	return 0;
}

static int boe_nt51017_10_800p_prepare(struct drm_panel *panel)
{
	struct boe_nt51017_10_800p *ctx = to_boe_nt51017_10_800p(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	pr_warn("Start prepare panel BOE NT51017_10_800p");

	if (ctx->prepared)
		return 0;

	boe_nt51017_10_800p_reset(ctx);

	ret = boe_nt51017_10_800p_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int boe_nt51017_10_800p_unprepare(struct drm_panel *panel)
{
	struct boe_nt51017_10_800p *ctx = to_boe_nt51017_10_800p(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = boe_nt51017_10_800p_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

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
};

static int boe_nt51017_10_800p_get_modes(struct drm_panel *panel,
					 struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &boe_nt51017_10_800p_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs boe_nt51017_10_800p_panel_funcs = {
	.prepare = boe_nt51017_10_800p_prepare,
	.unprepare = boe_nt51017_10_800p_unprepare,
	.get_modes = boe_nt51017_10_800p_get_modes,
};

static int boe_nt51017_10_800p_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int boe_nt51017_10_800p_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness & 0xff;
}

static const struct backlight_ops boe_nt51017_10_800p_bl_ops = {
	.update_status = boe_nt51017_10_800p_bl_update_status,
	.get_brightness = boe_nt51017_10_800p_bl_get_brightness,
};

static struct backlight_device *
boe_nt51017_10_800p_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &boe_nt51017_10_800p_bl_ops, &props);
}

static int boe_nt51017_10_800p_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct boe_nt51017_10_800p *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	drm_panel_init(&ctx->panel, dev, &boe_nt51017_10_800p_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = boe_nt51017_10_800p_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static void boe_nt51017_10_800p_remove(struct mipi_dsi_device *dsi)
{
	struct boe_nt51017_10_800p *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id boe_nt51017_10_800p_of_match[] = {
	{ .compatible = "boe,nt51017-10-800p" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, boe_nt51017_10_800p_of_match);

static struct mipi_dsi_driver boe_nt51017_10_800p_driver = {
	.probe = boe_nt51017_10_800p_probe,
	.remove = boe_nt51017_10_800p_remove,
	.driver = {
		.name = "panel-boe-nt51017-10-800p",
		.of_match_table = boe_nt51017_10_800p_of_match,
	},
};
module_mipi_dsi_driver(boe_nt51017_10_800p_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for BOE_NT51017_10_800P_VIDEO");
MODULE_LICENSE("GPL");
