#include "vga.h"
#include "kernel.h"
#include "cursor.h"
#include "lib.h"
#include "keyboard.h"

uchar *vga = VGA_ENTRY;

void scroll_up(void)
{
	for (i32 y = 0; y < VGA_HEIGHT - 1; y++)
		copy_line(y + 1, y);

	clear_line(VGA_HEIGHT - 1);
	vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);
}

void copy_line(i32 src, i32 dest)
{
	uchar *src_entry = VGA_ENTRY + src * VGA_LINE;
	uchar *dest_entry = VGA_ENTRY + dest * VGA_LINE;

	for (i32 i = 0; i < VGA_WIDTH; i++) {
		COPY_CHAR(src_entry, dest_entry);
		src_entry += 2;
		dest_entry += 2;
	}
}

void clear_screen(void)
{
	uchar *screen_entry = VGA_ENTRY;

	for (i32 i = 0; i < VGA_SIZE; i++) {
		BLANK_CELL(screen_entry, get_theme()->bg_color);
		screen_entry += 2;
	}

	vga = VGA_ENTRY;
}

void clear_line(i32 line)
{
	uchar *line_entry = VGA_ENTRY + line * VGA_LINE;

	for (i32 i = 0; i < VGA_WIDTH; i++) {
		BLANK_CELL(line_entry, get_theme()->bg_color);
		line_entry += 2;
	}
}

void centered_print(const char *str)
{
	i32 len = strlenk(str);
	i32 padding = ((VGA_WIDTH - len) / 2);

	for (i32 i = 0; i < padding; i++) {
		putchark(' ');
	}

	putstrk(str);
	putchark('\n');
}
