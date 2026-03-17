#ifndef	VGA_H
#define	VGA_H

/* ================= Includes ================= */

#include "types.h"

/* ================= Macros / Constants ================= */

#define BLANK_CELL(buffer, bg_color) {						\
	(buffer)[0] = ' ';										\
	(buffer)[1] = (unsigned char)((bg_color << 4) | GRAY);	\
}

#define COPY_CHAR(src, dest) {	\
	dest[0]	= src[0];			\
	dest[1]	= src[1];			\
}

#define	VGA_WIDTH		80
#define	VGA_HEIGHT		25
#define	VGA_ENTRY		(unsigned char *) 0xB8000
#define	VGA_LINE		VGA_WIDTH * 2
#define	VGA_SIZE		(VGA_WIDTH * VGA_HEIGHT) * 2
#define	VGA_END			VGA_ENTRY + VGA_SIZE

/* ================= Enums ================= */

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

/* ================= Forward Declarations ================= */

/* ================= Structs ================= */

/* ================= External Tables / Globals ================= */

extern unsigned char	*g_vga;
extern unsigned char	*vga_end;

/* ================= Inline Functions ================= */

/* ================= Function Prototypes ================= */

void	clear_line(int line);
void	clear_screen();
void	copy_line(int src, int dest);
void	scroll_up();
void	shift_chars_right(unsigned char *pos);
void	centered_print(const char *str);
void	boot_screen();

#endif

