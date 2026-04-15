#ifndef CPU_H
#define CPU_H

#include "binary.h"

enum {
	CPU_HALT_BIT = 0 // 0000 0001
};

typedef struct s_cpu {
	uint8_t flags;
	// 0: halted
	// 1: unused
	// 2: unused
	// 3: unused
	// 4: unused
	// 5: unused
	// 6: unused
	// 7: unused
} t_cpu;

extern t_cpu	*g_cpu;

static inline bool get_cpu_halted(t_cpu *cpu) {
	return get_flag(cpu->flags, CPU_HALT_BIT);
}

static inline void set_cpu_halted(t_cpu *cpu, bool value) {
	set_flag(&cpu->flags, CPU_HALT_BIT, value);
}

#endif


