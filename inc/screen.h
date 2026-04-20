#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "shell.h"
#include "vga.h"
#include "theme.h"

#define MAX_SCREENS 13
#define CMD_BUFFER_SIZE 256

typedef struct s_kernel t_kernel;

extern t_kernel g_kernel;

typedef struct 		s_screen {
	unsigned char	buffer[VGA_SIZE];
	char			cmd_buffer[CMD_BUFFER_SIZE];
	uint8_t			cursor_row;
	uint8_t			cursor_col;
	uint8_t			cmd_index;
	bool			switched;
	t_theme			theme;
}					t_screen;

typedef struct		s_display {
	t_screen		screens[MAX_SCREENS];
	uint8_t			current;
}					t_display;

t_screen	*get_current_screen();
t_theme		*get_current_theme();
void		screen_changer(uint8_t key);
void 		init_display();

#endif
