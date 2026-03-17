#ifndef SCREEN_H
#define SCREEN_H

/* ================= Includes ================= */

#include "types.h"
#include "shell.h"
#include "vga.h"

/* ================= Macros / Constants ================= */

#define MAX_SCREENS 13
#define CMD_BUFFER_SIZE 256

/* ================= Enums ================= */

/* ================= Forward Declarations ================= */

typedef struct s_kernel t_kernel;

extern t_kernel g_kernel;

/* ================= Structs ================= */

typedef struct 		s_screen {
	unsigned char	buffer[VGA_SIZE];
	char			cmd_buffer[CMD_BUFFER_SIZE];
	uint8_t			cursor_row;
	uint8_t			cursor_col;
	uint8_t			theme;
	uint8_t			cmd_index;
	bool			switched;
}					t_screen;

typedef struct		s_screens {
	t_screen		screens[MAX_SCREENS];
	uint8_t			current;
}					t_screens;

/* ================= External Tables / Globals ================= */

/* ================= Function Prototypes ================= */

t_screen	*current_screen();
void		screen_changer(uint8_t key);
void 		init_screens(t_screens *screens);

#endif
