#include "lib.h"
#include "vga.h"
#include "screen.h"
#include "kernel.h"
#include "keyboard.h"
#include "cursor.h"

static void handle_newline()
{
	vga += (VGA_LINE) - ((vga - VGA_ENTRY) % (VGA_LINE));

	if (vga >= VGA_END)
		scroll_up();
}

static void handle_tab(struct screen *screen)
{
	i32 current_x = ((vga - VGA_ENTRY) / 2) % VGA_WIDTH;

	if (current_x > VGA_WIDTH - TAB_SIZE)
		scroll_up();

	vga += TAB_SIZE * 2;
	screen->cmd_index += TAB_SIZE;
}

static void handle_backspace(struct screen *screen)
{
	vga -= 2;
	BLANK_CELL(vga, get_current_screen()->theme.bg_color);
	screen->cmd_index--;
	screen->cmd_buffer[screen->cmd_index] = '\0';
}

static bool format_handler(i32 c)
{
	struct screen *screen = get_current_screen();

	switch (c) {
	case '\n':
		handle_newline();
		return true;
	case '\t':
		handle_tab(screen);
		return true;
	case '\b':
		handle_backspace(screen);
		return true;
	case '\r':
		vga -= (vga - VGA_ENTRY);
		return true;
	case '\v':
		vga += VGA_LINE;
		return true;
	}

	return false;
}

i32 writek(i32 c, i32 len)
{
	struct theme *theme = get_theme();

	for (i32 i = 0; i < len; i++) {
		if (true == format_handler(c))
			continue;

		if (vga >= VGA_END)
			scroll_up();

		*vga++ = (uchar)c;
		*vga++ = vga_attr(theme);
	}
	move_cursor();

	return len;
}
