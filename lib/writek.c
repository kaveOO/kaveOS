#include "lib.h"

static int format_handler(int c)
{
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
			return 1;
		}
		case '\b':
		{
			t_screen *screen = current_screen();
			if (screen->cmd_index == 0)
				return 1;
			g_vga -= 2;
			BLANK_CELL(g_vga);
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
	unsigned int fg = (g_kernel.color == 42) ? WHITE : g_kernel.color;
	unsigned int attr = (g_kernel.bg_color << 4) | (fg & 0x0F);

	for (int i = 0; i < len; i++) {
		if (format_handler(c)) {
			continue;
		}
		if (g_vga >= vga_end) {
			scroll_up();
		}
		if (*g_vga != ' ' && !KEYBOARD_INSERT_ON(&g_kernel.keyboard)) {
			shift_chars_right(g_vga);
		}
		*g_vga++ = (unsigned char)c;
		*g_vga++ = (unsigned char)attr;
	}
	move_cursor();
	return len;
}
