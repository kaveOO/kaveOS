#ifndef SHELL_H
#define SHELL_H

/* ================= Includes ================= */

#include "stack.h"
#include "lib.h"
#include "screen.h"
#include "cpu.h"
#include "io.h"
#include "keyboard.h"

/* ================= Macros / Constants ================= */

#define CMD_BUFFER_SIZE	256

/* ================= Enums ================= */

/* ================= Forward Declarations ================= */

typedef struct s_kernel t_kernel;

extern t_kernel g_kernel;

/* ================= Structs ================= */

/* ================= External Tables / Globals ================= */

/* ================= Inline Functions ================= */

/* ================= Function Prototypes ================= */

void	shell();

#endif
