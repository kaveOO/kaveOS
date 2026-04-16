#include "screen.h"
#include "kernel.h"

static bool get_screen_from_key(uint8_t key, unsigned int *screen_out) {
	if (get_shift_pressed(g_keyboard) && key < sizeof(f_keys_to_int)) {
		uint8_t screen = f_keys_to_int[key];
		if (screen == g_kernel.screens.current) {
			return false;
		}
		if (screen > 0 && screen <= 12) {
			*screen_out = screen;
			return true;
		}
	}
	return false;
}

static void save_screen_state() {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		g_kernel.screens.screens[g_kernel.screens.current].buffer[i] = vga_start[i];
	}

	int cursor_pos = (g_vga - VGA_ENTRY) / 2;
	g_kernel.screens.screens[g_kernel.screens.current].cursor_row = (uint8_t)(cursor_pos / VGA_WIDTH);
	g_kernel.screens.screens[g_kernel.screens.current].cursor_col = (uint8_t)(cursor_pos % VGA_WIDTH);
}

static void load_screen(unsigned int index) {
	unsigned char *vga_start = VGA_ENTRY;
	t_screen *screen = &g_kernel.screens.screens[index];

	for (int i = 0; i < VGA_SIZE; i += 2) {
		vga_start[i] = screen->buffer[i];
		vga_start[i + 1] = (unsigned char)((g_kernel.bg_color << 4) | (screen->buffer[i + 1] & 0x0F));
	}

	g_kernel.screens.current = (uint8_t)index;
	g_vga = VGA_ENTRY + (screen->cursor_row * VGA_WIDTH + screen->cursor_col) * 2;
	update_cursor(screen->cursor_row, screen->cursor_col);
}

void screen_changer(uint8_t key) {
	unsigned int screen;

	if (get_screen_from_key(key, &screen)) {
		if (g_kernel.screens.screens[screen].theme == 42) {
			g_kernel.color = 42;
		} else {
			g_kernel.color = g_kernel.screens.screens[screen].theme;
		}
		save_screen_state();
		load_screen(screen);
		if (g_kernel.screens.screens[screen].switched == false && g_kernel.screens.current != 1) {
			printk("kaveOS> \0 ");
		}
		g_kernel.screens.screens[screen].switched = true;
	}
}

void init_display(t_display *screens) {
	for (int i = 1; i <= 12; i++) {
		screens->screens[i].cursor_col = 0;
		screens->screens[i].cursor_row = 0;
		screens->screens[i].theme = 42;
		screens->screens[i].switched = false;
		for (int j = 0; j < VGA_SIZE; j += 2) {
			BLANK_CELL(&screens->screens[i].buffer[j], g_kernel.bg_color);
		}
		memsetk(
			screens->screens[i].cmd_buffer,
			0,
			sizeof(screens->screens[i].cmd_buffer)
		);
		screens->screens[i].cmd_index = 0;
	}
}

t_screen *get_current_screen() {
	return &g_kernel.screens.screens[g_kernel.screens.current];
}
