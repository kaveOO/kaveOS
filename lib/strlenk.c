#include "lib.h"

int strlenk(const char *str) {
	int	i = 0;

	while (str[i]) {
		i++;
	}
	return i;
}
