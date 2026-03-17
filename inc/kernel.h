#ifndef KERNEL_H
#define KERNEL_H

/* ================= Includes ================= */

#include "keyboard.h"
#include "screen.h"
#include "cpu.h"

/* ================= Macros / Constants ================= */

/* ================= Enums ================= */

/* ================= Forward Declarations ================= */

/* ================= Structs ================= */

typedef struct		s_kernel {
	t_keyboard		keyboard;
	t_screens		screens;
	t_cpu			cpu;
	unsigned int	color;
	unsigned int	bg_color;
} 					t_kernel;

/* ================= External Tables / Globals ================= */

extern t_kernel g_kernel;

/* ================= Inline Functions ================= */

/* ================= Function Prototypes ================= */


#endif

