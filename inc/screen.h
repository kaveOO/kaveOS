#ifndef SCREEN_H
#define SCREEN_H

#include "kernel.h"

static inline t_screen *current_screen() {
	return &g_kernel.screens.screens[g_kernel.screens.current];
}

void screen_changer(uint8_t key);
void init_screens(t_screens *screens);

#endif
