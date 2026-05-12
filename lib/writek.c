#include "lib.h"
#include "vga.h"
#include "screen.h"
#include "kernel.h"
#include "keyboard.h"
#include "cursor.h"

static void handle_newline()
{
	g_vga += (VGA_LINE) - ((g_vga - VGA_ENTRY) % (VGA_LINE));

	if (g_vga >= vga_end)
		scroll_up();
}

static void handle_tab(t_screen *screen)
{
	i32 current_x = ((g_vga - VGA_ENTRY) / 2) % VGA_WIDTH;

	if (current_x > VGA_WIDTH - TAB_SIZE)
		scroll_up();

	g_vga += TAB_SIZE * 2;
	screen->cmd_index += TAB_SIZE;
}

static void handle_backspace(t_screen *screen)
{
	g_vga -= 2;
	BLANK_CELL(g_vga, get_current_screen()->theme.bg_color);
	screen->cmd_index--;
	screen->cmd_buffer[screen->cmd_index] = '\0';
}

static bool format_handler(char c)
{
	t_screen *screen = get_current_screen();

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
		g_vga -= (g_vga - VGA_ENTRY);
		return true;
	case '\v':
		g_vga += VGA_LINE;
		return true;
	}

	return false;
}

i32 writek(i32 c, i32 len)
{
	t_theme *theme = get_current_theme();

	for (i32 i = 0; i < len; i++) {
		if (true == format_handler(c))
			continue;

		if (g_vga >= vga_end)
			scroll_up();

		*g_vga++ = (uchar)c;
		*g_vga++ = vga_attr(theme);
	}
	move_cursor();

	return len;
}
