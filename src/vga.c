#include "vga.h"
#include "kernel.h"
#include "cursor.h"
#include "lib.h"
#include "keyboard.h"

unsigned char *g_vga	= VGA_ENTRY;
unsigned char *vga_end	= VGA_END;

void scroll_up() {
	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		copy_line(y + 1, y);
	}

	clear_line(VGA_HEIGHT - 1);
	g_vga = VGA_ENTRY + ((VGA_HEIGHT - 1) * VGA_WIDTH * 2);
	move_cursor();
}

void copy_line(int src, int dest) {
	unsigned char *src_entry = VGA_ENTRY + src * VGA_LINE;
	unsigned char *dest_entry = VGA_ENTRY + dest * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		COPY_CHAR(src_entry, dest_entry);
		src_entry += 2;
		dest_entry += 2;
	}
}

void clear_screen() {
	unsigned char *screen_entry = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		BLANK_CELL(screen_entry, g_kernel.bg_color);
		screen_entry += 2;
	}
	g_vga = VGA_ENTRY;
	update_cursor(0, 0);
}

void clear_line(int line) {
	unsigned char *line_entry = VGA_ENTRY + line * VGA_LINE;

	for (int i = 0; i < VGA_WIDTH; i++) {
		BLANK_CELL(line_entry, g_kernel.bg_color);
		line_entry += 2;
	}
}

void centered_print(const char *str) {
	int len = strlenk(str);
	int padding = ((VGA_WIDTH - len) / 2);

	for (int i = 0; i < padding; i++) {
		putchark(' ');
	}

	putstrk(str);
	putchark('\n');
}

void boot_screen() {
	g_kernel.color = PURPLE;
	printk("\n\n\n\n");

	centered_print("  _                    ____   _____ ");
	centered_print(" | |                  / __ \\ / ____|");
	centered_print(" | | ____ ___   _____| |  | | (___  ");
	centered_print(" | |/ / _` \\ \\ / / _ \\ |  | |\\___ \\ ");
	centered_print(" |   < (_| |\\ V /  __/ |__| |____) |");
	centered_print(" |_|\\_\\__,_| \\_/ \\___|\\____/|_____/ ");

	putchark('\n');
	putchark('\n');

	g_kernel.color = CYAN;
	centered_print("Made by kaveO - https://github.com/kaveOO");

	putchark('\n');
	putchark('\n');

	putchark('\n');
	g_kernel.color = RED;
	centered_print("[ PRESS ENTER TO START ]");
	g_kernel.color = WHITE;

	while (!get_enter_pressed(g_keyboard)) {
		asm volatile("hlt");
	}

	g_kernel.color = WHITE;
	clear_screen();
}
