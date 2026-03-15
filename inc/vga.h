#ifndef	VGA_H
#define	VGA_H

#include "kernel.h"

extern	unsigned char	*g_vga;
extern	unsigned char	*vga_end;

enum Colors { // https://www.fountainware.com/EXPL/vga_color_palettes.htm
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	YELLOW,
	WHITE
};

#define BLANK_CELL(buffer) {										\
	(buffer)[0] = ' ';												\
	(buffer)[1] = (unsigned char)((g_kernel.bg_color << 4) | GRAY);	\
}

#define COPY_CHAR(src, dest) {	\
	dest[0]	= src[0];			\
	dest[1]	= src[1];			\
}

void	clear_line(int line);
void	clear_screen();
void	copy_line(int src, int dest);
void	scroll_up();
void	shift_chars_right(unsigned char *pos);
void	centered_print(const char *str);
void	boot_screen();

#endif

