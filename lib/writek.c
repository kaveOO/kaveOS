#include "lib.h"
#include "vga.h"
#include "screen.h"
#include "kernel.h"
#include "keyboard.h"
#include "cursor.h"

static int format_handler(int c) {
	t_screen *screen = get_current_screen();

	switch (c) {
		case '\n':
			g_vga += (VGA_LINE) - ((g_vga - VGA_ENTRY) % (VGA_LINE));
			if (g_vga >= vga_end) {
				scroll_up();
			}
			return 1;
		case '\t':
		{
			int current_x = ((g_vga - VGA_ENTRY) / 2) % VGA_WIDTH;
			if (current_x > VGA_WIDTH - 8) {
				scroll_up();
			}
			g_vga += 16;
			screen->cmd_index += 8;
			return 1;
		}
		case '\b':
		{
			g_vga -= 2;
			BLANK_CELL(g_vga, get_current_screen()->theme.bg_color);
			screen->cmd_index--;
			screen->cmd_buffer[screen->cmd_index] = '\0';
			return 1;
		}
		case '\r':
			g_vga -= (g_vga - VGA_ENTRY);
			return 1;
		case '\v':
			g_vga += VGA_LINE;
			return 1;
	}
	return 0;
}

int writek(int c, int len) {
	t_theme *theme = get_current_theme();

	for (int i = 0; i < len; i++) {
		if (format_handler(c)) {
			continue;
		}
		if (g_vga >= vga_end) {
			scroll_up();
		}

		*g_vga++ = (unsigned char)c;
		*g_vga++ = vga_attr(theme->color, theme->bg_color);
	}

	move_cursor();
	return len;
}
