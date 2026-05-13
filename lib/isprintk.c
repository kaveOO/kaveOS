#include <lib.h>

bool isprintk(i32 c)
{
	if (c >= 32 && c <= 126)
		return true;
	return false;
}
