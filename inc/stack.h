#ifndef STACK_H
#define STACK_H

#include "types.h"

#define DUMP_SIZE 16 // 8 or 16

enum StackType {
	GDT,
	IDT,
	KERNEL,
	KERNEL_EXEC,
};

extern u32	stack_top[];
extern u32	stack_bottom[];
extern u32 gdt_start[];
extern u32 gdt_end[];
extern u32 idt_start[];
extern u32 idt_end[];

static inline u32 get_esp() {
	u32 esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	return esp;
}

static inline u32 get_ebp() {
	u32 ebp;
	asm volatile("mov %%ebp, %0" : "=r"(ebp));
	return ebp;
}

void	hexdump(unsigned char *start, unsigned char *end);
void	print_stack(enum StackType stack);

#endif
