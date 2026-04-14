#ifndef CURSOR_H
#define CURSOR_H

#include "types.h"
#include "vga.h"
#include "io.h"

#define	CURSOR_CMD	0x3D4
#define	CURSOR_DATA	0x3D5

void	update_cursor(int row, int col);
void 	move_cursor();
int		get_cursor_x();
int		get_cursor_y();

#endif
