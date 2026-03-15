#include "theme.h"

static void replace_vga_theme(unsigned int color) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[1] = (unsigned char)color;
		vga_start += 2;
	}
}

static bool get_theme_from_key(uint8_t key, unsigned int *theme_out) {
	if (!KEYBOARD_L_SHIFT_PRESSED(&g_kernel.keyboard) && key < sizeof(f_keys_to_int)) {
		uint8_t theme = f_keys_to_int[key];
		if (theme > 0 && theme <= 12) {
			*theme_out = theme;
			return true;
		}
	}
	return false;
}

void theme_changer(uint8_t key) {
	unsigned int theme;
	if (get_theme_from_key(key, &theme)) {
		replace_vga_theme(theme);
		current_screen()->theme = (uint8_t)theme;
		g_kernel.color = theme;
	}
}
