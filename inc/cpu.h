#ifndef CPU_H
#define CPU_H

/* ================= Includes ================= */

#include "binary.h"

/* ================= Macros / Constants ================= */

/* ================= Enums ================= */

enum {
	CPU_HALT_BIT = 0 // 0000 0001
};

/* ================= Forward Declarations ================= */

/* ================= Structs ================= */

typedef struct		s_cpu {
	uint8_t			flags;
	// 0: halted
}					t_cpu;

/* ================= External Tables / Globals ================= */

extern t_cpu	*g_cpu;

/* ================= Inline Functions ================= */

static inline bool get_cpu_halted(t_cpu *cpu) {
	return get_flag(cpu->flags, CPU_HALT_BIT);
}

static inline void set_cpu_halted(t_cpu *cpu, bool value) {
	set_flag(&cpu->flags, CPU_HALT_BIT, value);
}

/* ================= Function Prototypes ================= */

#endif


