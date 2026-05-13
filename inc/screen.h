#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "shell.h"
#include "vga.h"
#include "theme.h"

#define MAX_SCREENS 13
#define CMD_BUFFER_SIZE 256

/// @brief Get screen VGA offset from cursor values
/// @param row screen cursor row
/// @param col screen cursor col
/// @return VGA position of the screen
static inline uchar *get_offset(u8 row, u8 col)
{
	return VGA_ENTRY + 2 * (row * VGA_WIDTH + col);
}

struct screen {
	uchar		buffer[VGA_SIZE];
	char		cmd_buffer[CMD_BUFFER_SIZE];
	u8		cursor_row;
	u8		cursor_col;
	u8		cmd_index;
	bool		switched;
	struct theme	theme;
};

struct screen 	*get_current_screen();
struct theme	*get_current_theme();
void		screen_changer(u8 key);
void 		init_display();
void		init_screen(struct screen *screen);

#endif
