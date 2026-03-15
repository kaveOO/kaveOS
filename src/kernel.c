#include "kernel.h"

unsigned char *video = VGA_ENTRY;
unsigned char *end = VGA_END;

// TODO const values on the left side of conditions

// TODO not default test for non zero (view norm)

// TODO: Pass as parameter for better modularity

t_kernel	g_kernel;
t_keyboard	*g_keyboard = &g_kernel.keyboard;
t_cpu		*g_cpu = &g_kernel.cpu;

void kernel_init() {
	g_kernel.keyboard.flags = 0;
	g_kernel.cpu.flags = 0;
	g_kernel.color = 42;
	g_kernel.bg_color = BLACK;
	init_screens(&g_kernel.screens);
	g_kernel.screens.current = 1;
	boot_screen();
}

void kmain() {
	kernel_init();
	shell();
}
