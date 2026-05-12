#include "lib.h"

int strncmpk(const char *s1, const char *s2, u32 n)
{
	u32 i = 0;

	if (n == 0)
		return (0);

	while (s1[i] == s2[i] && s1[i] != '\0') {
		if (i < (n - 1))
			i++;
		else
			return (0);
	}

	return ((uchar)(s1[i]) - (uchar)(s2[i]));
}
