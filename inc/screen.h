#ifndef SCREEN_H
#define SCREEN_H

#include "kernel.h"

t_screen *current_screen();

void screen_changer(uint8_t key);
void init_screens(t_screens *screens);

#endif
