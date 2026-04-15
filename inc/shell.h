#ifndef SHELL_H
#define SHELL_H

#include "stack.h"
#include "lib.h"
#include "screen.h"
#include "cpu.h"
#include "io.h"
#include "keyboard.h"

#define CMD_BUFFER_SIZE	256

typedef struct s_kernel		t_kernel;
typedef struct s_keyboard	t_keyboard;

extern t_kernel g_kernel;

void	shell(t_keyboard *keyboard);

#endif
