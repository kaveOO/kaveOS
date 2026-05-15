#ifndef TYPES_H
#define TYPES_H

#define bool	int
#define true	1
#define false	0

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned char		uchar;

typedef	uchar			u8;
typedef	unsigned short		u16;
typedef	unsigned int		u32;

typedef	signed char		i8;
typedef	signed short		i16;
typedef	signed int		i32;

typedef	char			*va_list;
#define	va_start(ap,parmn)	(void)((ap) = (char*)(&(parmn) + 1))
#define	va_end(ap) 		(void)((ap) = 0)
#define	va_arg(ap, type)	(((type*)((ap) = ((ap) + sizeof(type))))[-1])

#endif
