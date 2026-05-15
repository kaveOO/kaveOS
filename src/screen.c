#include <screen.h>
#include <kernel.h>
#include <cursor.h>
#include <lib.h>

struct screen (*screens)[MAX_SCREENS] = &kernel.display.screens;

static struct screen *get_screen_from_key(u8 key)
{
	u8 index = f_keys_to_int[key];

	if (get_display()->current == index)
		return NULL;

	if (index > 0 && index <= 12)
		return &(*screens)[index];

	return NULL;
}

static void save_screen_state(void)
{
	uchar *vga_start = VGA_ENTRY;
	struct screen *screen = get_current_screen();

	for (int i = 0; i < VGA_SIZE; i++)
		screen->buffer[i] = vga_start[i];

	screen->cursor_row = get_cursor_row();
	screen->cursor_col = get_cursor_col();
}

static void load_screen(u8 index)
{
	uchar *vga_start = VGA_ENTRY;
	struct screen *sc = &(*screens)[index];

	for (int i = 0; i < VGA_SIZE; i += 2) {
		vga_start[i] = sc->buffer[i];
		vga_start[i + 1] = vga_attr(&sc->theme);
	}

	get_display()->current = index;
	vga = get_offset(sc->cursor_row, sc->cursor_col);
}

void screen_changer(u8 key)
{
	struct screen *screen = get_screen_from_key(key);

	if (screen) {
		u8 index = f_keys_to_int[key];

		save_screen_state();
		load_screen(index);

		if (false == screen->switched && get_display()->current != 1)
			printk("%d - kaveOS> ", get_display()->current);
		screen->switched = true;
	}
}

void init_screen(struct screen *screen)
{
	screen->cursor_col = 0;
	screen->cursor_col = 0;
	screen->theme.color = WHITE;
	screen->theme.bg_color = BLACK;
	screen->switched = false;

	for (int i = 0; i < VGA_SIZE; i += 2)
		BLANK_CELL(&screen->buffer[i], BLACK);

	memsetk(screen->cmd_buffer, 0, sizeof(screen->cmd_buffer));
}

struct screen *get_current_screen()
{
	return &(*screens)[get_display()->current];
}

