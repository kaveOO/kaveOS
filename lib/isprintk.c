#include "lib.h"

bool isprintk(int c) {
	if (c >= 32 && c <= 126) {
		return true;
	}
	return false;
}
