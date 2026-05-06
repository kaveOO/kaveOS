#include "keyboard.h"
#include "kernel.h"

t_keyboard *kbd = &g_kernel.keyboard;

const u8 f_keys_to_int[0x59] = {
	[F1] = 1,
	[F2] = 2,
	[F3] = 3,
	[F4] = 4,
	[F5] = 5,
	[F6] = 6,
	[F7] = 7,
	[F8] = 8,
	[F9] = 9,
	[F10] = 10,
	[F11] = 11,
	[F12] = 12
};

const char scancode_shifted[128] = {
	0,  27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b', '\t',
	'Q','W','E','R','T','Y','U','I','O','P','{','}','\n', 0,
	'A','S','D','F','G','H','J','K','L',':','"','~', 0,
	'|','Z','X','C','V','B','N','M','<','>','?', 0,  '*', 0, ' '
};

const char scancode_normal[128] = {
	0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
	'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
	'a','s','d','f','g','h','j','k','l',';','\'', '`', 0,
	'\\','z','x','c','v','b','n','m',',','.','/', 0,  '*', 0, ' '
};

static void update_modifiers(u8 key, t_key_state state)
{
	if (SHIFT == key)
		set_shift_pressed(kbd, state == KEY_PRESSED);
	else if (CONTROL == key)
		set_ctrl_pressed(kbd, state == KEY_PRESSED);
	else if (CAPS_LOCK == key && state == KEY_PRESSED)
		set_caps_lock_on(kbd, !get_caps_lock_on(kbd));
}

/// @brief Translate a key to a character
/// @param key The key pressed (sent by keyboard_handler)
/// @return The character corresponding to the key pressed
static char key_to_char(u8 key)
{
	char c = ZERO;

	if (get_shift_pressed(kbd))
		c = scancode_shifted[key];
	else
		c = scancode_normal[key];

	if (c >= 'a' && c <= 'z') {
		if (get_caps_lock_on(kbd) ^ get_shift_pressed(kbd))
			return (char)(c - 'a' + 'A');
	} else if (c >= 'A' && c <= 'Z') {
		if (get_caps_lock_on(kbd) ^ get_shift_pressed(kbd))
			return c;
		else
			return (char)(c - 'A' + 'a');
	}
	return c;
}

/// @brief Handle the cpu state from keyboard interruption
/// @param key The key pressed (sent by keyboard_handler)
static void handle_cpu_state(u8 key)
{
	if (get_cpu_halted(g_cpu))
		if (0x13 == key)
			set_cpu_halted(g_cpu, false);
}


static void handle_special_keys(u8 key, t_key_state state)
{
	if (state != KEY_PRESSED)
		return;

	switch (key) {
	case RIGHT_ARROW:
		g_vga += 2;
		break;
	case LEFT_ARROW:
		if (get_current_screen()->cmd_index > 0)
			g_vga -= 2;
		break;
	default:
		break;
	}
	move_cursor();
}

static void process_input_char(t_screen *screen, char c) {
	if (!get_enter_pressed(kbd) && NEW_LINE != c) {
		return;
	} else if (NEW_LINE == c) {
		if (!get_cmd_ready(kbd)) {
			if (!get_enter_pressed(kbd)) {
				set_enter_pressed(kbd, true);
				return;
			}
		}
		screen->cmd_buffer[screen->cmd_index] = '\0';
		set_cmd_ready(kbd, true);
		printk("\n");
	} else if (BACKSPACE == c) {
		if (screen->cmd_index > 0) {
			printk("\b");
		}
	} else if (TAB == c) {
		printk("\t");
	} else {
		if (screen->cmd_index < CMD_BUFFER_SIZE - 1) {
			screen->cmd_buffer[screen->cmd_index++] = c;
			char buf[2] = { c, '\0' };
			printk(buf);
		}
	}
}

void keyboard_handler() {
	u8 scancode = inb(KEYBOARD_DATA_PORT);
	t_key_state state = (scancode & KEY_RELEASED) ? KEY_RELEASED : KEY_PRESSED;
	u8 key = scancode & 0x7F;

	handle_cpu_state(key);
	update_modifiers(key, state);
	theme_changer(key);
	if (get_shift_pressed(kbd))
		screen_changer(key);

	char c = key_to_char(key);
	handle_special_keys(key, state);
    if (c && KEY_PRESSED == state && !get_cpu_halted(g_cpu)) {
        process_input_char(get_current_screen(), c);
    }
}
