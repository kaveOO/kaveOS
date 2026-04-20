#include "theme.h"
#include "vga.h"
#include "keyboard.h"
#include "screen.h"
#include "kernel.h"

static void replace_vga_theme(t_theme *theme) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[1] = vga_attr(theme->color, theme->bg_color);
		vga_start += 2;
	}
}

static t_theme *set_theme_from_key(uint8_t key) {
	t_theme *theme = get_current_theme();
	enum Colors color;

	if (!get_shift_pressed(g_keyboard)) {
		color = f_keys_to_int[key];
		if (color > 0 && color <= 12) {
			if (get_ctrl_pressed(g_keyboard)) {
				theme->bg_color = color;
			} else {
				theme->color = color;
			}
			return theme;
		}
	}

	return NULL;
}

void theme_changer(uint8_t key) {
	t_theme *theme = set_theme_from_key(key);

	if (theme) {
		replace_vga_theme(theme);
	}
}
