#include "keyboard.h"
#include "stack.h"
#include "cpu.h"

static void	update_modifiers(uint8_t key, t_key_state state) {
	if (LEFT_SHIFT == key) {
		SET_KEYBOARD_L_SHIFT_PRESSED(g_keyboard, state == KEY_PRESSED);
	} else if (RIGHT_SHIFT == key) {
		SET_KEYBOARD_R_SHIFT_PRESSED(g_keyboard, state == KEY_PRESSED);
	} else if (CONTROL == key) {
		SET_KEYBOARD_CTRL_PRESSED(g_keyboard, state == KEY_PRESSED);
	} else if (CAPS_LOCK == key && state == KEY_PRESSED) {
		SET_KEYBOARD_CAPS_LOCK_ON(g_keyboard, !KEYBOARD_CAPS_LOCK_ON(g_keyboard));
	}
}

static char	translate_scancode(uint8_t scancode) {
	uint8_t key = scancode & 0x7F;
	char c = 0;

	if (KEYBOARD_L_SHIFT_PRESSED(g_keyboard)) {
		c = scancode_shifted[key];
	} else {
		c = scancode_normal[key];
	}

	if (c >= 'a' && c <= 'z') {
		if (KEYBOARD_CAPS_LOCK_ON(g_keyboard) ^ KEYBOARD_L_SHIFT_PRESSED(g_keyboard)) {
			return (char)(c - 'a' + 'A');
		}
	} else if (c >= 'A' && c <= 'Z') {
		if (KEYBOARD_CAPS_LOCK_ON(g_keyboard) ^ KEYBOARD_L_SHIFT_PRESSED(g_keyboard)) {
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

	if ((c == 'r' || c == 'R') && KEYBOARD_CTRL_PRESSED(g_keyboard) && 		get_cpu_halted(g_cpu)) {
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
		case INSERT:
			SET_KEYBOARD_INSERT_ON(g_keyboard, !KEYBOARD_INSERT_ON(g_keyboard));
			break;
		default:
			break;
	}
	move_cursor();
}

static void process_input_char(t_screen *screen, char c) {
	if (!KEYBOARD_IS_ENTER_PRESSED(g_keyboard) && NEW_LINE != c) {
		return;
	} else if (NEW_LINE == c) {
		if (!KEYBOARD_IS_CMD_READY(g_keyboard)) {
			if (!KEYBOARD_IS_ENTER_PRESSED(g_keyboard)) {
				SET_KEYBOARD_IS_ENTER_PRESSED(g_keyboard, true);
				return;
			}
		}
		screen->cmd_buffer[screen->cmd_index] = '\0';
		SET_KEYBOARD_IS_CMD_READY(g_keyboard, true);
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
        process_input_char(current_screen(), c);
    }
}
