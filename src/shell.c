#include "shell.h"
#include "cpu.h"

void help() {
	printk("F1-F12        \tchange the text and write color of current screen\n");
	printk("Shift + F1-F12\tswitch between available screens\n");
	printk("help          \tlist of available commands\n");
	printk("stack         \tprint the kernel stack\n");
	printk("exec          \tprint the kernel execution stack\n");
	printk("gdt           \tprint the gdt stack\n");
	printk("clear         \tclear the terminal of actual screen\n");
	printk("halt          \thalt the kernel execution (Ctrl + R) to resume\n");
	printk("reboot        \treboot the kernel\n");
}

void exec_cmd(const char *line) {
	if (is_str_equal(line, "stack")) print_stack(KERNEL);
	else if (is_str_equal(line, "exec")) print_stack(KERNEL_EXEC);
	else if (is_str_equal(line, "clear")) clear_screen();
	else if (is_str_equal(line, "help")) help();
	else if (is_str_equal(line, "gdt")) print_stack(GDT);
	else if (is_str_equal(line, "idt")) print_stack(IDT);
	else if (is_str_equal(line, "halt")) {
		set_cpu_halted(g_cpu, true);
		while (get_cpu_halted(g_cpu)) asm volatile("hlt");
	}
	else if (is_str_equal(line, "reboot")) outb(0x64, 0xFE);
	else printk("command not found: %s\n", line);
}

void shell() {
	printk("kaveOS> \0 ", g_kernel.screens.current);
	while (1) {
		while (!get_cmd_ready(g_keyboard)) {
			// Wait for \n signal, halting is mandatory for race conditions
			asm volatile("hlt");
		}
		t_screen *screen = current_screen();
		char *line = screen->cmd_buffer;
		if (line[0]) exec_cmd(line);
		screen->cmd_index = 0;
		set_cmd_ready(g_keyboard, false);
		memsetk(
			screen->cmd_buffer,
			0,
			sizeof(screen->cmd_buffer)
		);
		printk("kaveOS> \0 ", g_kernel.screens.current);
	}
}
