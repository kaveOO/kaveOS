#include <screen.h>
#include <kernel.h>
#include <cursor.h>

struct screen (*screens)[MAX_SCREENS] = &kernel.display.screens;

/// @brief Get screen index from key
/// @param key The key sent by keyboard isr
/// @return Screen index (if key 1 - 12)
static struct screen *get_screen_from_key(u8 key)
{
	u8 index = f_keys_to_int[key];

	if (get_display()->current == index)
		return NULL;

	if (index > 0 && index <= 12)
		return &(*screens)[index];

	return NULL;
}

/// @brief Save the current screen data in struct
static void save_screen_state(void)
{
	uchar *vga_start = VGA_ENTRY;
	struct screen *screen = get_current_screen();

	for (int i = 0; i < VGA_SIZE; i++)
		screen->buffer[i] = vga_start[i];

	screen->cursor_row = get_cursor_row();
	screen->cursor_col = get_cursor_col();
}

/// @brief Load the screen that correspond to the index
/// @param index The index of the screen to load
static void load_screen(u8 index)
{
	uchar *vga_start = VGA_ENTRY;
	struct screen *sc = &(*screens)[index];

	for (int i = 0; i < VGA_SIZE; i += 2) {
		vga_start[i] = sc->buffer[i];
		vga_start[i + 1] = vga_attr(&sc->theme);
	}

	get_display()->current = index;
	g_vga = get_offset(sc->cursor_row, sc->cursor_col);
}

/// @brief Save current screen and load a new screen from key
/// @param key The key which correspond to index of screen to load
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

/// @brief Init a screen by setting default values
/// @param screen The screen to init
void init_screen(struct screen *screen)
{
	screen->cursor_col = ZERO;
	screen->cursor_col = ZERO;
	screen->theme.color = WHITE;
	screen->theme.bg_color = BLACK;
	screen->switched = false;

	for (int i = 0; i < VGA_SIZE; i += 2)
		BLANK_CELL(&screen->buffer[i], BLACK);

	memsetk(screen->cmd_buffer, ZERO, sizeof(screen->cmd_buffer));
}

/// @brief Get a pointer to the current screen
/// @return A pointer to the actual screen
struct screen *get_current_screen()
{
	return &(*screens)[get_display()->current];
}

