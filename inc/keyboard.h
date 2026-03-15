#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

#define KEYBOARD_DATA_PORT	0x60
#define	LEFT_SHIFT			0x2A
#define RIGHT_SHIFT			0x36
#define CONTROL				0x1D
#define	CAPS_LOCK			0x3A
#define INSERT				0x52
#define RIGHT_ARROW			0x4D
#define LEFT_ARROW			0x4B

#define KEYBOARD_L_SHIFT_PRESSED(k)		((k)->flags & (1 << 0))
#define KEYBOARD_R_SHIFT_PRESSED(k)		((k)->flags & (1 << 1))
#define KEYBOARD_CTRL_PRESSED(k)		((k)->flags & (1 << 2))
#define KEYBOARD_INSERT_ON(k)			((k)->flags & (1 << 3))
#define KEYBOARD_CAPS_LOCK_ON(k)		((k)->flags & (1 << 4))
#define KEYBOARD_IS_CMD_READY(k)		((k)->flags & (1 << 5))
#define KEYBOARD_IS_ENTER_PRESSED(k)	((k)->flags & (1 << 6))

#define SET_KEYBOARD_L_SHIFT_PRESSED(k, val)	(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 0))) | ((val) ? (uint8_t)(1 << 0) : 0)
#define SET_KEYBOARD_R_SHIFT_PRESSED(k, val)	(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 1))) | ((val) ? (uint8_t)(1 << 1) : 0)
#define SET_KEYBOARD_CTRL_PRESSED(k, val)		(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 2))) | ((val) ? (uint8_t)(1 << 2) : 0)
#define SET_KEYBOARD_INSERT_ON(k, val)			(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 3))) | ((val) ? (uint8_t)(1 << 3) : 0)
#define SET_KEYBOARD_CAPS_LOCK_ON(k, val)		(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 4))) | ((val) ? (uint8_t)(1 << 4) : 0)
#define SET_KEYBOARD_IS_CMD_READY(k, val)		(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 5))) | ((val) ? (uint8_t)(1 << 5) : 0)
#define SET_KEYBOARD_IS_ENTER_PRESSED(k, val)	(k)->flags = ((k)->flags & (uint8_t)(0xFF ^ (1 << 6))) | ((val) ? (uint8_t)(1 << 6) : 0)

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
