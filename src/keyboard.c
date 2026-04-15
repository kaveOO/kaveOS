#include "keyboard.h"

const uint8_t f_keys_to_int[0x59] = {
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

static void	update_modifiers(uint8_t key, t_key_state state) {
	if (SHIFT == key) {
		set_shift_pressed(g_keyboard, state == KEY_PRESSED);
	} else if (CONTROL == key) {
		set_ctrl_pressed(g_keyboard, state == KEY_PRESSED);
	} else if (CAPS_LOCK == key && state == KEY_PRESSED) {
		set_caps_lock_on(g_keyboard, !get_caps_lock_on(g_keyboard));
	}
}

static char	translate_scancode(uint8_t scancode) {
	uint8_t key = scancode & 0x7F;
	char c = 0;

	if (get_shift_pressed(g_keyboard)) {
		c = scancode_shifted[key];
	} else {
		c = scancode_normal[key];
	}

	if (c >= 'a' && c <= 'z') {
		if (get_caps_lock_on(g_keyboard) ^ get_shift_pressed(g_keyboard)) {
			return (char)(c - 'a' + 'A');
		}
	} else if (c >= 'A' && c <= 'Z') {
		if (get_caps_lock_on(g_keyboard) ^ get_shift_pressed(g_keyboard)) {
			return c;
		} else {
			return (char)(c - 'A' + 'a');
		}
	}
	return c;
}

static void handle_special_keys(uint8_t scancode, char c, t_key_state state) {
	if (state != KEY_PRESSED) {
		return;
	}

	if ((c == 'r' || c == 'R') && get_ctrl_pressed(g_keyboard) && 		get_cpu_halted(g_cpu)) {
		set_cpu_halted(g_cpu, false);
		return;
	}

	uint8_t key = scancode & 0x7F;

	switch (key) {
		case RIGHT_ARROW:
			g_vga += 2;
			break;
		case LEFT_ARROW:
			g_vga -= 2;
			break;
		default:
			break;
	}
	move_cursor();
}

static void process_input_char(t_screen *screen, char c) {
	if (!get_enter_pressed(g_keyboard) && NEW_LINE != c) {
		return;
	} else if (NEW_LINE == c) {
		if (!get_cmd_ready(g_keyboard)) {
			if (!get_enter_pressed(g_keyboard)) {
				set_enter_pressed(g_keyboard, true);
				return;
			}
		}
		screen->cmd_buffer[screen->cmd_index] = '\0';
		set_cmd_ready(g_keyboard, true);
		printk("\n");
	} else if (BACKSPACE == c) {
		if (0 < screen->cmd_index) {
			printk("\b");
		}
	} else {
		if (screen->cmd_index < CMD_BUFFER_SIZE - 1) {
			screen->cmd_buffer[screen->cmd_index++] = c;
			char buf[2] = { c, '\0' };
			printk(buf);
		}
	}
}

void keyboard_handler() {
	uint8_t scancode = inb(KEYBOARD_DATA_PORT);
	t_key_state state = (scancode & KEY_RELEASED) ?
						KEY_RELEASED : KEY_PRESSED;
	uint8_t key = scancode & 0x7F;

	update_modifiers(key, state);
	theme_changer(key);
	screen_changer(key);

	char c = translate_scancode(scancode);
	handle_special_keys(scancode, c, state);
    if (c && KEY_PRESSED == state && !get_cpu_halted(g_cpu)) {
        process_input_char(get_current_screen(), c);
    }
}
