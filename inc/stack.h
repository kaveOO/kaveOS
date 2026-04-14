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

extern uint32_t	stack_top[];
extern uint32_t	stack_bottom[];
extern uint32_t gdt_start[];
extern uint32_t gdt_end[];
extern uint32_t idt_start[];
extern uint32_t idt_end[];

static inline uint32_t get_esp() {
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	return esp;
}

static inline uint32_t get_ebp() {
	uint32_t ebp;
	asm volatile("mov %%ebp, %0" : "=r"(ebp));
	return ebp;
}

void	hexdump(unsigned char *start, unsigned char *end);
void	print_stack(enum StackType stack);

#endif
