#include "lib.h"

static int print_hex_up(unsigned int nb) {
	int count = 0;
	char *hex = "0123456789ABCDEF";

	if (nb >= 16) {
		count += print_hex_up(nb / 16);
	}
	count += putchark(hex[nb % 16]);
	return count;
}

static int print_hex_low(unsigned int nb) {
	int count = 0;
	char *hex = "0123456789abcdef";

	if (nb >= 16) {
		count += print_hex_low(nb / 16);
	}
	count += putchark(hex[nb % 16]);
	return count;
}

static int putnbrk(int nb) {
	int count = 0;

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

int printk(const char *str, ...) {
	va_list list;
	va_start(list, str);
	int count = 0;

	for (int i = 0; str[i]; i++) {
		if (PERCENT == str[i]) {
			i++;
			switch (str[i]) {
				case 'c':
					count += putchark(va_arg(list, int));
					break;
				case 's':
					count += putstrk(va_arg(list, const char *));
					break;
				case 'd':
				case 'i':
					count += putnbrk(va_arg(list, int));
					break;
				case 'x':
					count += print_hex_low(va_arg(list, unsigned int));
					break;
				case 'X':
					count += print_hex_up(va_arg(list, unsigned int));
					break;
			}
			i++;
		}
		count += writek(str[i], 1);
	}
	va_end(list);
	return count;
}
