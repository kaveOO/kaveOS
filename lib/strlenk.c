#include "lib.h"

i32 strlenk(const char *str)
{
	i32 i = 0;

	while (str[i])
		i++;

	return i;
}
