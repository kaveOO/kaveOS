#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <types.h>

#define KEYBOARD_DATA_PORT	0x60
#define	SHIFT			0x2A
#define CONTROL			0x1D
#define	CAPS_LOCK		0x3A
#define RIGHT_ARROW		0x4D
#define LEFT_ARROW		0x4B

#define F1	0x3B
#define F2	0x3C
#define F3	0x3D
#define F4	0x3E
#define F5	0x3F
#define F6	0x40
#define F7	0x41
#define F8	0x42
#define F9	0x43
#define F10	0x44
#define F11	0x57
#define F12	0x58

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

static const u8 f_keys_to_int[0x59] = {
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

enum key_state {
	KEY_RELEASED = 0x80,
	KEY_PRESSED = 0x00
};

enum {
	KB_SHIFT_BIT = 0,
	KB_CTRL_BIT = 1,
	KB_CAPS_LOCK_BIT = 2,
	KB_ENTER_BIT = 3,
	KB_CMD_READY_BIT = 4
};

struct keyboard {
	u8 flags;
	// 0: shift_pressed
	// 1: ctrl_pressed
	// 2: caps_lock_on
	// 3: is_cmd_ready
	// 4: is_enter_pressed
	// 5: unused
	// 6: unused
	// 7: unused
};

extern const u8	f_keys_to_int[0x59];
extern const char scancode_shifted[128];
extern const char scancode_normal[128];

bool get_shift_pressed(void);
bool get_ctrl_pressed(void);
bool get_caps_lock_on(void);
bool get_cmd_ready(void);
bool get_enter_pressed(void);
void set_shift_pressed(bool value);
void set_ctrl_pressed(bool value);
void set_caps_lock_on(bool value);
void set_cmd_ready(bool value);
void set_enter_pressed(bool value);

#endif
