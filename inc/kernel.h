#ifndef KERNEL_H
#define KERNEL_H

#include "keyboard.h"
#include "screen.h"
#include "cpu.h"

typedef struct		s_kernel {
	t_keyboard		keyboard;
	t_screens		screens;
	t_cpu			cpu;
	unsigned int	color;
	unsigned int	bg_color;
} 					t_kernel;

extern t_kernel g_kernel;

#endif

