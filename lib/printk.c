#include "lib.h"

static i32 print_hex_up(u32 nb)
{
	i32 count = 0;
	char *hex = "0123456789ABCDEF";

	if (nb >= 16)
		count += print_hex_up(nb / 16);
	count += putchark(hex[nb % 16]);

	return count;
}

static i32 print_hex_low(u32 nb)
{
	i32 count = 0;
	char *hex = "0123456789abcdef";

	if (nb >= 16)
		count += print_hex_low(nb / 16);
	count += putchark(hex[nb % 16]);

	return count;
}

static i32 putnbrk(i32 nb)
{
	i32 count = 0;

	if (-2147483648 == nb) {
		count += putstrk("-2147483648");
		return count;
	} else if (nb < 0) {
		count += writek('-', 1);
		nb = -nb;
	} else if (nb < 10) {
		count += writek(nb + '0', 1);
	} else {
		count += putnbrk(nb / 10);
		count += putnbrk(nb % 10);
	}

	return count;
}

static i32 print_address(const u32 nb)
{
	i32 count = 0;

	if (nb >= 16)
		count += print_address(nb / 16);

	if (nb % 16 < 10)
		count += putchark((nb % 16) + '0');
	else
		count += putchark((nb % 16) - 10 + 'a');

	return count;
}

static i32 hex_len(u32 nb)
{
	i32 len = 1;

	while (nb >= 16) {
		nb /= 16;
		len++;
	}

	return len;
}

static i32 printptrk(void *address)
{
	u32 addr = (u32)address;
	i32 len = 0;
	i32 width = sizeof(void *) * 2;
	i32 digits;

	len += putstrk("0x");

	if (!address) {
		for (i32 i = 0; i < width; i++)
			len += putchark('0');
		return len;
	}

	digits = hex_len(addr);

	for (i32 i = 0; i < width - digits; i++)
		len += putchark('0');
	len += print_address(addr);

	return len;
}

i32 format_handler(char format, va_list list)
{
	i32 count = 0;

	switch (format) {
	case 'c':
		count += putchark(va_arg(list, i32));
		break;
	case 's':
		count += putstrk(va_arg(list, const char *));
		break;
	case 'd':
	case 'i':
		count += putnbrk(va_arg(list, i32));
		break;
	case 'x':
		count += print_hex_low(va_arg(list, u32));
		break;
	case 'X':
		count += print_hex_up(va_arg(list, u32));
		break;
	case 'p':
		count += printptrk(va_arg(list, void *));
	}

	return count;
}

i32 printk(const char *str, ...)
{
	va_list list;
	va_start(list, str);
	i32 count = 0;

	for (i32 i = 0; str[i]; i++) {
		if (PERCENT == str[i]) {
			i++;
			count += format_handler(str[i], list);
			i++;
		}
		count += writek(str[i], 1);
	}
	va_end(list);

	return count;
}
