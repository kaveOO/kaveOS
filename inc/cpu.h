#ifndef CPU_H
#define CPU_H

#include "kernel.h"
#include "binary.h"

enum {
	CPU_HALT_BIT = 0 // 0000 0001
};

static inline bool get_cpu_halted(t_cpu *cpu) {
	return get_flag(cpu->flags, CPU_HALT_BIT);
}

static inline void set_cpu_halted(t_cpu *cpu, bool value) {
	set_flag(&cpu->flags, CPU_HALT_BIT, value);
}

#endif
