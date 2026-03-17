#ifndef IO_H
#define IO_H

/* ================= Includes ================= */

#include "types.h"

/* ================= Macros / Constants ================= */

/* ================= Enums ================= */

/* ================= Forward Declarations ================= */

/* ================= Structs ================= */

/* ================= External Tables / Globals ================= */

/* ================= Inline Functions ================= */

static inline void outb(uint16_t port, uint8_t val) {
	__asm__ volatile ( "outb %b0, %w1"
						:
						: "a"(val), "Nd"(port)
						: "memory");
}

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	__asm__ volatile ( "inb %w1, %b0"
						: "=a"(ret)
						: "Nd"(port)
						: "memory");
	return ret;
}

/* ================= Function Prototypes ================= */

#endif
