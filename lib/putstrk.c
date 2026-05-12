#include "lib.h"

i32 putstrk(const char *str)
{
	i32 len = strlenk(str);

	for (i32 i = 0; i < len; i++)
		writek(str[i], 1);

	return len;
}
