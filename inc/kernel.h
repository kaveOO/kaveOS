#ifndef KERNEL_H
#define KERNEL_H

#include <display.h>
#include <keyboard.h>
#include <cpu.h>

struct kernel {
	struct keyboard	keyboard;
	struct display	display;
	struct cpu	cpu;
};

extern struct kernel kernel;

#endif

