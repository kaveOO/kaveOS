#include <kernel.h>

struct kernel kernel;

void kernel_init(void)
{
	kernel.keyboard.flags = 0;
	kernel.cpu.flags = 0;
	kernel.display.current = 1;
	init_display();
}

void kmain()
{
	kernel_init();
	shell();
}
