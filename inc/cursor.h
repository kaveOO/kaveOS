#ifndef CURSOR_H
#define CURSOR_H

#include <types.h>
#include <vga.h>

#define	CURSOR_CMD	0x3D4
#define	CURSOR_DATA	0x3D5

static inline u8 get_cursor_row(void)
{
	return (u8)(((g_vga - VGA_ENTRY) / 2) / VGA_WIDTH);
}

static inline u8 get_cursor_col(void)
{
	return (u8)(((g_vga - VGA_ENTRY) / 2) % VGA_WIDTH);
}

void 	move_cursor(void);

#endif
