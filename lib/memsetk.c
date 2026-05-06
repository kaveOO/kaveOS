#include "lib.h"

void *memsetk(void *ptr, int value, unsigned long num) {
	uchar *p = (uchar *)ptr;

	while (num--) {
		*p++ = (uchar)value;
	}
	return ptr;
}
