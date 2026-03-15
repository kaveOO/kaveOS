#ifndef CPU_H
#define CPU_H

#include "kernel.h"

enum CpuFlags {
	CPU_FLAG_HALTED = 0 // 0000 0001
};

static inline bool get_cpu_halted(t_cpu *cpu) {
	return cpu->flags & BIT(CPU_FLAG_HALTED)
}

static inline void set_cpu_halted(t_cpu *cpu, bool value) {
	if (value) {
		cpu->flags |= BIT(CPU_FLAG_HALTED);
	} else {
		cpu->flags &= (uint8_t)~BIT(CPU_FLAG_HALTED);
	}
}

#endif
