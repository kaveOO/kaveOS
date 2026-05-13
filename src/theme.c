#include "theme.h"
#include "vga.h"
#include "keyboard.h"
#include "screen.h"
#include "kernel.h"

struct theme *get_theme(void)
{
	return &get_current_screen()->theme;
}

static void replace_vga_theme(struct theme *theme)
{
	uchar *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[1] = vga_attr(theme);
		vga_start += 2;
	}
}

static struct theme *set_theme_from_key(u8 key)
{
	struct theme *theme = get_theme();
	enum colors color;

	if (!get_shift_pressed()) {
		color = f_keys_to_int[key];
		if (color > 0 && color <= 12) {
			if (get_ctrl_pressed())
				theme->bg_color = color;
			else
				theme->color = color;
			return theme;
		}
	}

	return NULL;
}

void theme_changer(u8 key)
{
	struct theme *theme = set_theme_from_key(key);

	if (theme)
		replace_vga_theme(theme);
}

u8 vga_attr(struct theme *theme)
{
	return (uchar)(theme->bg_color << 4) | (theme->color & 0x0F);
}
