#include "vga.h"
#include "kernel.h"
#include "cursor.h"
#include "lib.h"
#include "keyboard.h"

uchar *g_vga	= VGA_ENTRY;
uchar *vga_end	= VGA_END;

void scroll_up() {
	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		copy_line(y + 1, y);
	}

	clear_line(VGA_HEIGHT - 1);
	g_vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);
}

void copy_line(int src, int dest) {
	uchar *src_entry = VGA_ENTRY + src * VGA_LINE;
	uchar *dest_entry = VGA_ENTRY + dest * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		COPY_CHAR(src_entry, dest_entry);
		src_entry += 2;
		dest_entry += 2;
	}
}

void clear_screen() {
	uchar *screen_entry = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		BLANK_CELL(screen_entry, get_current_screen()->theme.bg_color);
		screen_entry += 2;
	}

	g_vga = VGA_ENTRY;
}

void clear_line(int line) {
	uchar *line_entry = VGA_ENTRY + line * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		BLANK_CELL(line_entry, get_current_screen()->theme.bg_color);
		line_entry += 2;
	}
}

void centered_print(const char *str) {
	int len = strlenk(str);
	int padding = ((VGA_WIDTH - len) / 2);

	for (int i = 0; i < padding; i++) {
		putchark(' ');
	}

	putstrk(str);
	putchark('\n');
}
