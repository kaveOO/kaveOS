#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include "binary.h"
#include "cpu.h"
#include "vga.h"
#include "cursor.h"
#include "chars.h"
#include "screen.h"
#include "lib.h"
#include "theme.h"

#define KEYBOARD_DATA_PORT	0x60
#define	SHIFT				0x2A
#define CONTROL				0x1D
#define	CAPS_LOCK			0x3A
#define RIGHT_ARROW			0x4D
#define LEFT_ARROW			0x4B

// TODO set keys as enum

#define F1					0x3B
#define F2					0x3C
#define F3					0x3D
#define F4					0x3E
#define F5					0x3F
#define F6					0x40
#define F7					0x41
#define F8					0x42
#define F9					0x43
#define F10					0x44
#define F11					0x57
#define F12					0x58

typedef enum {
	KEY_RELEASED = 0x80,
	KEY_PRESSED = 0x00
} t_key_state;

enum {
	KB_SHIFT_BIT		= 0,
	KB_CTRL_BIT 		= 1,
	KB_CAPS_LOCK_BIT 	= 2,
	KB_ENTER_BIT 		= 3,
	KB_CMD_READY_BIT 	= 4
};

typedef struct		s_keyboard {
	uint8_t			flags;
	// 0: shift_pressed
	// 1: ctrl_pressed
	// 2: caps_lock_on
	// 3: is_cmd_ready
	// 4: is_enter_pressed
	// 5: unused
	// 6: unused
	// 7: unused
}					t_keyboard;

extern const uint8_t	f_keys_to_int[0x59];
extern const char		scancode_shifted[128];
extern const char		scancode_normal[128];

extern t_keyboard		*g_keyboard;

static inline bool get_shift_pressed(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_SHIFT_BIT);
}

static inline bool get_ctrl_pressed(t_keyboard *keyboard) {
	return get_flag(keyboard->flags, KB_CTRL_BIT);
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

static inline void set_shift_pressed(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_SHIFT_BIT, value);
}

static inline void set_ctrl_pressed(t_keyboard *keyboard, bool value) {
	set_flag(&keyboard->flags, KB_CTRL_BIT, value);
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

#endif
