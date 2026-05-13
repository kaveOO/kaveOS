#ifndef DISPLAY_H
#define DISPLAY_H

#include <types.h>
#include <screen.h>

struct display {
	struct screen screens[MAX_SCREENS];
	u8 current;
};

struct display *get_display(void);

#endif
