#ifndef CURSOR_H
#define CURSOR_H

#include "types.h"
#include "vga.h"
#include "io.h"

#define	CURSOR_CMD	0x3D4
#define	CURSOR_DATA	0x3D5

static inline u8 get_cursor_row() {
	return (u8)(((g_vga - VGA_ENTRY) / 2) / VGA_WIDTH);
}

static inline u8 get_cursor_col() {
	return (u8)(((g_vga - VGA_ENTRY) / 2) % VGA_WIDTH);
}

void	update_cursor(int row, int col);
void 	move_cursor();
int	get_cursor_x();
int	get_cursor_y();

#endif
