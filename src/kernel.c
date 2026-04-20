#include "kernel.h"

// TODO const values on the left side of conditions

// TODO not default test for non zero (view norm)

// TODO: Pass as parameter for better modularity

// TODO get_cpu_halted -> is_cpu_halted


t_kernel	g_kernel;
t_cpu		*g_cpu = &g_kernel.cpu;
t_keyboard	*g_keyboard;

void kernel_init() {
	g_kernel.keyboard.flags = 0;
	g_kernel.cpu.flags = 0;
	init_display();
	g_kernel.screens.current = 1;
	boot_screen();
}

void kmain() {
	g_keyboard = &g_kernel.keyboard;
	g_cpu = &g_kernel.cpu;
	kernel_init();
	shell(g_keyboard);
}
