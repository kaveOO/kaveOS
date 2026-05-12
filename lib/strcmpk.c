#include "lib.h"

i32 strcmpk(const char *s1, const char *s2)
{
	i32 i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;

	return (s1[i]-s2[i]);
}
