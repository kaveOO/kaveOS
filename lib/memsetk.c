#include <lib.h>

void *memsetk(void *ptr, i32 value, u32 num)
{
	uchar *p = (uchar *)ptr;

	while (num--)
		*p++ = (uchar)value;
	return ptr;
}
