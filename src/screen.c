#include "screen.h"
#include "kernel.h"

t_display *display = &g_kernel.screens;

static t_screen *get_screen_from_key(uint8_t key) {
	uint8_t index = f_keys_to_int[key];

	if (display->current == index) {
		return NULL;
	}

	if (index > 0 && index <= 12) {
		return &display->screens[index];
	}

	return NULL;
}

static void save_screen_state() {
	unsigned char *vga_start = VGA_ENTRY;
	t_screen *screen = get_current_screen();

	for (int i = 0; i < VGA_SIZE; i++) {
		screen->buffer[i] = vga_start[i];
	}

	screen->cursor_row = get_cursor_row();
	screen->cursor_col = get_cursor_col();
}

static unsigned char *get_offset(uint8_t row, uint8_t col) {
	return VGA_ENTRY + 2 * (row * VGA_WIDTH + col);
}

static void load_screen(uint8_t index) {
	unsigned char *vga_start = VGA_ENTRY;
	t_screen *screen = &display->screens[index];

	for (int i = 0; i < VGA_SIZE; i += 2) {
		vga_start[i] = screen->buffer[i];
		vga_start[i + 1] = vga_attr(screen->buffer[i + 1], screen->theme.bg_color);
	}

	display->current = index;
	g_vga = get_offset(screen->cursor_row, screen->cursor_col);
}

void screen_changer(uint8_t key) {
	t_screen *screen = get_screen_from_key(key);

	if (screen && get_shift_pressed(g_keyboard)) {
		uint8_t index = f_keys_to_int[key];

		save_screen_state();
		load_screen(index);

		if (false == screen->switched && display->current != 1) {
			printk("%d - kaveOS> \0 ", display->current);
		}

		screen->switched = true;
	}
}

void init_display() {
	for (int i = 1; i <= 12; i++) {
		display->screens[i].cursor_col = 0;
		display->screens[i].cursor_row = 0;
		display->screens[i].theme.color = WHITE;
		display->screens[i].theme.bg_color = BLACK;
		display->screens[i].switched = false;

		for (int j = 0; j < VGA_SIZE; j += 2) {
			BLANK_CELL(
				&display->screens[i].buffer[j],
				BLACK
			);
		}

		memsetk(
			display->screens[i].cmd_buffer,
			0,
			sizeof(display->screens[i].cmd_buffer)
		);

		display->screens[i].cmd_index = 0;
	}
}

t_screen *get_current_screen() {
	return &display->screens[display->current];
}

t_theme *get_current_theme() {
	return &display->screens[display->current].theme;
}
