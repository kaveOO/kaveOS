#include <display.h>
#include <kernel.h>

struct display *display = &kernel.display;

/// @brief Initalization of display structure
void init_display(void)
{
	for (u8 i = 1; i < MAX_SCREENS; i++)
		init_screen(&display->screens[i]);
}

/// @brief Get a pointer on display struct (member of kernel)
struct display *get_display(void)
{
	return display;
}

