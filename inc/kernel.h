#ifndef KERNEL_H
#define KERNEL_H

#define BIT(n) (1u << (n));

#define	VGA_WIDTH		80
#define	VGA_HEIGHT		25
#define	VGA_ENTRY		(unsigned char *) 0xB8000
#define	VGA_LINE		VGA_WIDTH * 2
#define	VGA_SIZE		(VGA_WIDTH * VGA_HEIGHT) * 2
#define	VGA_END			VGA_ENTRY + VGA_SIZE

typedef struct	s_keyboard	t_keyboard;
typedef struct	s_screens	t_screens;
typedef struct	s_screen	t_screen;
typedef struct	s_shell		t_shell;
typedef struct	s_kernel	t_kernel;
typedef struct	s_cpu		t_cpu;

extern t_kernel		g_kernel;
extern t_keyboard	*g_keyboard;
extern t_shell		*g_shell;
extern t_cpu		*g_cpu;

#include "vga.h"
#include "cursor.h"
#include "io.h"
#include "keyboard.h"
#include "shell.h"
#include "theme.h"
#include "structs.h"
#include "screen.h"
#include "stack.h"
#include "const.h"
#include "lib.h"
#include "types.h"

#endif

