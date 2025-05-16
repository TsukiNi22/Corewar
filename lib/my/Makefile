##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the compilation of the lib
##

CC := gcc

TARGET := libmy.a
BUILD_DIR := .obj

W := -W -Wall -Wextra -Wpedantic -Wunused-parameter -Wshadow
W += -Wuninitialized -Wmaybe-uninitialized

DEBUG := -g -ggdb3

CPPFLAGS := -I ../../include/
LDFLAGS := -lm
CFLAGS := $(W)

ifeq ($(d), t)
	CFLAGS := $(DEBUG)
else ifeq ($(d), o)
	CFLAGS += -O1
endif

MEMORY :=	memory/my_realloc.c \
			memory/my_malloc.c \
			memory/my_calloc.c \
         	memory/my_strdup.c \
         	memory/my_strndup.c

STRING := 	string/cmp/my_strncmp.c \
			string/cmp/my_strcmp.c \
			string/cmp/my_str_is.c \
			string/edit/my_strcat.c \
			string/edit/my_strcpy.c \
			string/edit/my_strncat.c \
			string/edit/my_strncpy.c \
			string/retrive/count_occurence.c \
			string/retrive/my_get_index.c \
			string/retrive/my_strlen.c \
			string/retrive/my_strstr.c \
			string/retrive/my_strfind.c \
			string/transformation/convertnbr_base.c \
			string/transformation/get_fullpath.c \
			string/transformation/str_to_str_array.c \
			string/transformation/my_itoa.c \
			string/transformation/my_atoi.c \
			string/transformation/cut_str.c

WRITE := 	write/my_putchar.c \
			write/my_putstr.c \
        	write/my_putnbr.c \
			write/my_putnbr_base.c \
			write/edit_ouput/color/back_color.c \
			write/edit_ouput/color/back_color_rgb.c \
			write/edit_ouput/color/color_rgb.c \
			write/edit_ouput/color/color.c \
			write/edit_ouput/style/strong.c \
			write/edit_ouput/reset.c

ARRAY := 	array/new_array.c \
			array/add_array.c \
			array/pop_array.c \
			array/delete_array.c

FILE := 	file/get_file.c

ERROR :=	error/error_dispatch.c \
			error/error_print.c \
			error/error_prog.c \
			error/error_custom.c \
			error/error_system.c

SRC := $(MEMORY) $(STRING) $(WRITE) $(ARRAY) $(FILE)
SRC += $(ERROR)
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	@ar rc $@ $^
	@mv $@ ../

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f ../$(TARGET)

.NOTPARALLEL:
re: fclean $(TARGET)

get_unregistered_files:
	@find . -name "*.c" | sed "s/\.\///g" | while read file; do \
        	echo "$(SRC)" | grep -q "$$file" || \
		echo "$$file" >> new_files_detected.txt; \
        done
	@if [ -f new_files_detected.txt ]; then \
                cat new_files_detected.txt;\
                rm -f new_files_detected.txt; \
        fi

get_unknow_files:
	@for file in $(SRC); do \
            if [ ! -f "$$file" ]; then \
                echo "$$file" >> missing_files.txt; \
            fi; \
        done
	@if [ -f missing_files.txt ]; then \
                cat missing_files.txt | sed "s/src\///g"; \
                rm -f missing_files.txt; \
        fi

.PHONY: all clean fclean re get_unregistered_files get_unknow_files
