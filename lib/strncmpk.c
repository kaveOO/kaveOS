#include "lib.h"

int	strncmpk(const char *s1, const char *s2, unsigned int n) {
	unsigned int i = 0;

	if (n == 0) return (0);

	while (s1[i] == s2[i] && s1[i] != '\0') {
		if (i < (n - 1)) {
			i++;
		} else {
			return (0);
		}
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
