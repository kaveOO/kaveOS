#ifndef CURSOR_H
#define CURSOR_H

#include "types.h"
#include "vga.h"
#include "io.h"

#define	CURSOR_CMD	0x3D4
#define	CURSOR_DATA	0x3D5

static inline uint8_t get_cursor_row() {
	return (uint8_t)(((g_vga - VGA_ENTRY) / 2) / VGA_WIDTH);
}

static inline uint8_t get_cursor_col() {
	return (uint8_t)(((g_vga - VGA_ENTRY) / 2) % VGA_WIDTH);
}

void	update_cursor(int row, int col);
void 	move_cursor();
int		get_cursor_x();
int		get_cursor_y();

#endif
