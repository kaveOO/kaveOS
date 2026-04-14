#ifndef LIB_H
#define LIB_H

#include "types.h"
#include "chars.h"

int		strcmpk(const char *s1, const char *s2);

static inline bool is_str_equal(const char *s1, const char *s2) {
	return(0 == strcmpk(s1, s2));
}

int		putchark(int c);
int		putstrk(const char *str);
int		strlenk(const char *str);
int		writek(int c, int len);
int		printk(const char *str, ...);
int		strncmpk(const char *s1, const char *s2, unsigned int n);
void	*memsetk(void *ptr, int value, unsigned long num);
int		strcmpk(const char *s1, const char *s2);
bool	isprintk(int c);

#endif
