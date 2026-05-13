#include <cpu.h>
#include <kernel.h>

struct cpu *cpu = &kernel.cpu;

bool get_cpu_halted(void)
{
	return get_flag(cpu->flags, CPU_HALT_BIT);
}

void set_cpu_halted(bool value)
{
	set_flag(&cpu->flags, CPU_HALT_BIT, value);
}
