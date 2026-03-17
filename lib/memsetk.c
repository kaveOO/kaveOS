#include "lib.h"

void *memsetk(void *ptr, int value, unsigned long num) {
	unsigned char *p = (unsigned char *)ptr;

	while (num--) {
		*p++ = (unsigned char)value;
	}
	return ptr;
}
