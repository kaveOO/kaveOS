#ifndef VGA_H
#define VGA_H

#include <types.h>

#define BLANK_CELL(buffer, bg_color)			\
{							\
	(buffer)[0] = ' ';				\
	(buffer)[1] = (uchar)((bg_color << 4) | GRAY);	\
}

#define COPY_CHAR(src, dest)	\
{				\
	dest[0]	= src[0];	\
	dest[1]	= src[1];	\
}

#define	VGA_WIDTH	80
#define	VGA_HEIGHT	25
#define	VGA_ENTRY	(uchar *) 0xB8000
#define	VGA_LINE	VGA_WIDTH * 2
#define	VGA_SIZE	(VGA_WIDTH * VGA_HEIGHT) * 2
#define	VGA_END		VGA_ENTRY + VGA_SIZE

enum colors { // https://www.fountainware.com/EXPL/vga_color_palettes.htm
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

extern uchar *vga;

void clear_line(i32 line);
void clear_screen();
void copy_line(i32 src, i32 dest);
void scroll_up();
void centered_print(const char *str);

#endif

