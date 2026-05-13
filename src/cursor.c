#include <cursor.h>
#include <io.h>

void move_cursor(void)
{
	i32 pos = ((vga - VGA_ENTRY) / 2);

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (u8)(pos & 0xFF));

	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (u8)((pos >> 8) & 0xFF));
}
