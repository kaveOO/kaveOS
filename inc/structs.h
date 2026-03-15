#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

#define MAX_SCREENS 13

typedef struct		s_keyboard {
	uint8_t			flags;
	// 0: left_shift_pressed
	// 1: right_shift_pressed
	// 2: ctrl_pressed
	// 3: insert_on
	// 4: caps_lock_on
	// 5: is_cmd_ready
	// 6: is_enter_pressed
	// 7: unused
}					t_keyboard;

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

typedef struct		s_cpu {
	uint8_t			flags;
	// 0: halted
}					t_cpu;

typedef struct		s_kernel {
	t_keyboard		keyboard;
	t_screens		screens;
	t_cpu			cpu;
	unsigned int	color;
	unsigned int	bg_color;
} 					t_kernel;

#endif
