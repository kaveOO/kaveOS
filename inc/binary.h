#ifndef BINARY_H
#define BINARY_H

#include <types.h>

#define BIT(n) (1u << (n))

static inline bool get_flag(u8 flags, u8 bit)
{
	return (flags >> bit) & 1;
}

static inline void set_flag(u8 *flags, u8 bit, bool value)
{
	if (value)
		*flags |= BIT(bit);
	else
		*flags &= (u8)~BIT(bit);
}

#endif
