#ifndef CPU_H
#define CPU_H

#include "binary.h"

enum {
	CPU_HALT_BIT = 0 // 0000 0001
};

struct cpu {
	u8 flags;
	// 0: halted
	// 1: unused
	// 2: unused
	// 3: unused
	// 4: unused
	// 5: unused
	// 6: unused
	// 7: unused
};

bool get_cpu_halted(void);
void set_cpu_halted(bool value);

#endif


