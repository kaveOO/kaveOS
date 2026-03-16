#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include "binary.h"
#include "structs.h"

#define KEYBOARD_DATA_PORT	0x60
#define	SHIFT				0x2A
#define CONTROL				0x1D
#define	CAPS_LOCK			0x3A
#define INSERT				0x52
#define RIGHT_ARROW			0x4D
#define LEFT_ARROW			0x4B

enum {
	KB_SHIFT_BIT		= 0,
	KB_CTRL_BIT 		= 1,
	KB_INSERT_BIT 		= 2,
	KB_CAPS_LOCK_BIT 	= 3,
	KB_ENTER_BIT 		= 4,
	KB_CMD_READY_BIT 	= 5
};

// Binary Getters

static inline bool get_shift_pressed(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_SHIFT_BIT);
}

static inline bool get_ctrl_pressed(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_CTRL_BIT);
}

static inline bool get_insert_on(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_INSERT_BIT);
}

static inline bool get_caps_lock_on(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_CAPS_LOCK_BIT);
}

static inline bool get_cmd_ready(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_CMD_READY_BIT);
}

static inline bool get_enter_pressed(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_ENTER_BIT);
}

// Binary Setters

static inline void set_shift_pressed(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_SHIFT_BIT, value);
}

static inline void set_ctrl_pressed(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_CTRL_BIT, value);
}

static inline void set_insert_on(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_INSERT_BIT, value);
}

static inline void set_caps_lock_on(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_CAPS_LOCK_BIT, value);
}

static inline void set_cmd_ready(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_CMD_READY_BIT, value);
}

static inline void set_enter_pressed(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_ENTER_BIT, value);
}

typedef enum {
	KEY_RELEASED = 0x80,
	KEY_PRESSED = 0x00
} t_key_state;

static const char scancode_normal[128] = {
	0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
	'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
	'a','s','d','f','g','h','j','k','l',';','\'', '`', 0,
	'\\','z','x','c','v','b','n','m',',','.','/', 0,  '*', 0, ' '
};

static const char scancode_shifted[128] = {
	0,  27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b', '\t',
	'Q','W','E','R','T','Y','U','I','O','P','{','}','\n', 0,
	'A','S','D','F','G','H','J','K','L',':','"','~', 0,
	'|','Z','X','C','V','B','N','M','<','>','?', 0,  '*', 0, ' '
};

static const uint8_t f_keys_to_int[0x59] = {
	[0x3B] = 1,	// F1
	[0x3C] = 2,
	[0x3D] = 3,
	[0x3E] = 4,
	[0x3F] = 5,
	[0x40] = 6,
	[0x41] = 7,
	[0x42] = 8,
	[0x43] = 9,
	[0x44] = 10,
	[0x57] = 11,
	[0x58] = 12 // F12
};

extern bool resume_flag;
extern bool is_halted;

#endif
