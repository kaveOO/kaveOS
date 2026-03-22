# COLORS

PURPLE			=	\x1b[0m\x1b[38;2;128;0;128m
LIGHT_PURPLE	=	\x1b[0m\x1b[38;2;204;153;255m
DARK_PURPLE		=	\x1b[1m\x1b[38;2;75;0;130m

# VARIABLES

ISO_NAME 		= kaveOS.iso
BIN_NAME 		= kaveOS.bin
FLAGS 			= -Wall -Wextra -Werror -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -Wpedantic -Wconversion
QEMU_FLAGS		= -audiodev pa,id=speaker -machine pcspk-audiodev=speaker -full-screen

# -audiodev pa,id=speaker -machine pcspk-audiodev=speaker -full-screen

SRC_C			= $(wildcard src/*.c)
OBJ_C			= $(patsubst src/%.c,build/%.o,$(SRC_C))
OBJ_ASM			= build/boot.o
LIB_C			= $(wildcard lib/*.c)
OBJ_LIB			= $(patsubst lib/%.c,build/%.o,$(LIB_C))

# RULES

all: fclean build/$(BIN_NAME) build/$(ISO_NAME)

install:
	@echo -e '$(PURPLE)Installing required dependencies'
	@sudo apt install nasm
	@sudo apt install grub-pc
	@sudo apt install xorriso
	@sudo apt install qemu-system-i386

build/%.o: src/%.c
	@mkdir -p build
	@gcc -m32 $(FLAGS) -c $< -I inc -I lib -o $@
build/%.o: lib/%.c
	@mkdir -p build
	@gcc -m32 $(FLAGS) -c $< -I inc -I lib -o $@

build/boot.o: src/boot.s
	@mkdir -p build
	@nasm -f elf32 $< -o $@

build/$(BIN_NAME): $(OBJ_ASM) $(OBJ_C) $(OBJ_LIB)
	@ld -m elf_i386 -T src/linker.ld -o $@ $(OBJ_ASM) $(OBJ_C) $(OBJ_LIB)
	@echo -e '$(LIGHT_PURPLE) Linked $(DARK_PURPLE)kaveOS $(PURPLE)!'

build/$(ISO_NAME): build/$(BIN_NAME)
	@mv build/$(BIN_NAME) kaveOS/boot/$(BIN_NAME)
	@grub-mkrescue -o build/$(ISO_NAME) kaveOS/ > /dev/null 2>&1
	@mv build/$(ISO_NAME) kaveOS/boot
	@echo -e '\n$(LIGHT_PURPLE)-> make run <- $(PURPLE)to start the $(DARK_PURPLE)kaveOS $(PURPLE)!'

re: fclean all

clean:
	@rm -rf build
	@echo -e '$(LIGHT_PURPLE) Deleted $(PURPLE)build folder !'

fclean: clean
	@rm -rf kaveOS/boot/$(BIN_NAME) kaveOS/boot/$(ISO_NAME)
	@echo -e '$(LIGHT_PURPLE) Deleted $(PURPLE)boot files !'

run:
	@qemu-system-i386 $(QEMU_FLAGS) -cdrom kaveOS/boot/${ISO_NAME}
	@echo -e '$(LIGHT_PURPLE) Exited $(DARK_PURPLE)kaveOS $(PURPLE)!'
