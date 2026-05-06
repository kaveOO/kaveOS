#include "cursor.h"

void move_cursor() {
	int	pos = ((g_vga - VGA_ENTRY) / 2);

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (u8) (pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (u8) ((pos >> 8) & 0xFF));
}

void update_cursor(int row, int col) {
	int	pos = ((row * VGA_WIDTH) + col);

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (u8)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (u8)((pos >> 8) & 0xFF));
}

int get_cursor_x() {
	u16 pos = 0;

	outb(CURSOR_CMD, 0x0F);
	pos |= inb(CURSOR_DATA);
	outb(CURSOR_CMD, 0x0E);
	pos |= ((u16)inb(CURSOR_DATA)) << 8;

	int x = pos % VGA_WIDTH;
	return x;
}

int	get_cursor_y() {
	u16 pos = 0;

	outb(CURSOR_CMD, 0x0F);
	pos |= inb(CURSOR_DATA);
	outb(CURSOR_CMD, 0x0E);
	pos |= ((u16)inb(CURSOR_DATA)) << 8;

	int y = pos / VGA_WIDTH;
	return y;
}
