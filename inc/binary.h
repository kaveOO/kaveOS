#ifndef BINARY_H
#define BINARY_H

/* ================= Includes ================= */

#include "types.h"

/* ================= Macros / Constants ================= */

#define BIT(n) (1u << (n))

/* ================= Enums ================= */

/* ================= Forward Declarations ================= */

/* ================= Structs ================= */

/* ================= External Tables / Globals ================= */

/* ================= Inline Functions ================= */

static inline bool get_flag(uint8_t flags, uint8_t bit) {
	return (flags >> bit) & 1;
}

static inline void set_flag(uint8_t *flags, uint8_t bit, bool value) {
	if (value) {
		*flags |= BIT(bit);
	} else {
		*flags &= (uint8_t)~BIT(bit);
	}
}

/* ================= Function Prototypes ================= */

#endif
