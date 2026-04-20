#ifndef THEME_H
#define THEME_H

#include "types.h"
#include "vga.h"

typedef struct	s_theme {
	enum Colors	color;
	enum Colors	bg_color;
}				t_theme;

void	theme_changer(uint8_t key);

#endif
