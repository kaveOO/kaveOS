#include "stack.h"
#include "lib.h"
#include "vga.h"

void print_stack(enum StackType stack)
{
	switch (stack) {
	case GDT:
		hexdump((uchar *)&gdt_start, (uchar *)&gdt_end);
		break;
	case IDT:
		hexdump((uchar *)&idt_start, (uchar *)&idt_end);
		break;
	case KERNEL:
		hexdump((uchar *)&stack_bottom, (uchar *)&stack_top);
		break;
	case KERNEL_EXEC:
		hexdump((uchar *)get_esp(), (uchar *)&stack_top);
		break;
	default:
		printk("print_stack: invalid StackType\n");
		break;
	}
}

static void hex_view(uchar *start)
{
	char hex_digits[] = "0123456789abcdef";

	for (u8 i = 0; i < DUMP_SIZE; i++) {
		uchar byte = start[i];

		writek(hex_digits[byte >> 4], 1);
		writek(hex_digits[byte & 0xF], 1);
		writek(' ', 1);

		if (16 == DUMP_SIZE && 7 == i)
			writek(' ', 1);
	}
}

static void ascii_view(uchar *start)
{
	for (u8 i = 0; i < DUMP_SIZE; i++) {
		uchar c = start[i];

		if (isprintk(c))
			writek(c, 1);
		else
			writek('.', 1);
	}
}

void hexdump(uchar *start, uchar *end)
{
	while (start < end) {
		printk("%p  ", start);

		hex_view(start);

		writek(' ', 1);

		ascii_view(start);

		writek('\n', 1);
		start += DUMP_SIZE;
	}
}
