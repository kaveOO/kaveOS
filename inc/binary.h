#ifndef BINARY_H
#define BINARY_H

#include "types.h"

#define BIT(n) (1u << (n))

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

#endif
