#ifndef THEME_H
#define THEME_H

#include <types.h>
#include <vga.h>

struct theme {
	enum colors color;
	enum colors bg_color;
};

void	theme_changer(u8 key);
u8	vga_attr(struct theme *theme);
struct	theme *get_theme(void);

#endif
