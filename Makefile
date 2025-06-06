##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the compilation of the executable
##

CC := gcc

TARGET := corewar
TEST_TARGET := unit_tests
BUILD_DIR := .obj

W := -W -Wall -Wextra -Wpedantic -Wunused-parameter -Wshadow
W += -Wuninitialized -Wmaybe-uninitialized
CSFML := -lcsfml-graphics -lcsfml-window -lcsfml-system

DEBUG := -g -ggdb3

CPPFLAGS := -I ./include/
LDFLAGS := -L ./lib/ -lmy -lncurses
LDFLAGS += $(CSFML)
CFLAGS := $(W)

ifeq ($(d), t)
	CFLAGS := $(DEBUG)
else ifeq ($(d), o)
	CFLAGS += -O1
endif

GLOBAL :=	main.c \
			op.c \
			const.c \
			corewar.c \
			setup.c \
			update_cycle.c \
			exe_memory.c \
			dump.c \
			free_data.c

INIT :=		init/init_data.c \
			init/data/init_global.c \
			init/data/init_option.c \
			init/init_argument.c \
			init/init_champions.c \
			init/init_csfml.c \
			init/flag/null.c \
			init/flag/help.c \
			init/flag/dump.c \
			init/flag/ddump.c \
			init/flag/number.c \
			init/flag/address.c \
			init/flag/graphics.c \
			init/flag/csfml.c \
			init/flag/speed.c

OP_CMD := 	op_exe/param.c \
			op_exe/live.c \
			op_exe/ld.c \
			op_exe/st.c \
			op_exe/add.c \
			op_exe/sub.c \
			op_exe/and.c \
			op_exe/or.c \
			op_exe/xor.c \
			op_exe/zjmp.c \
			op_exe/ldi.c \
			op_exe/sti.c \
			op_exe/fork.c \
			op_exe/lld.c \
			op_exe/lldi.c \
			op_exe/lfork.c \
			op_exe/aff.c

GRAPHICS	:=	graphics_while.c

FILES := $(GLOBAL) $(INIT) $(OP_CMD) $(GRAPHICS)
RENDER := 	render/render_csfml.c \
			render/render_box.c \
			render/render_info.c \
			render/render_memory.c

FILES := $(GLOBAL) $(INIT) $(OP_CMD) $(RENDER) $(GRAPHICS)
SRC := $(addprefix src/, $(FILES))
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

TEST_OBJ := $(filter-out $(BUILD_DIR)/src/main.o, $(OBJ))

all: $(TARGET)

$(TARGET): $(OBJ)
	@make -C lib/my --no-print-directory d=$(d)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $^

lib:
	@rm -f $(TARGET)
	@make -j --no-print-directory

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f tests/*.o
	@rm -f *.gc*
	@rm -f vgcore.*
	@make clean -C lib/my --no-print-directory

fclean: clean
	@rm -f $(TARGET)
	@rm -f $(TEST_TARGET)
	@make fclean -C lib/my --no-print-directory

.NOTPARALLEL:
re: fclean $(TARGET)

unit_tests: $(TARGET)
	$(CC) -o $(TEST_TARGET) $(TEST_OBJ) tests/*.c \
	$(CPPFLAGS) $(LDFLAGS) --coverage -lcriterion

tests_run:    unit_tests
	@./$(TEST_TARGET)
	@gcovr . --exclude tests/ --exclude lib/

set_font:
	@echo "Setup the font in \'/usr/share/fonts/liberation-mono/\'..."
	@sudo mkdir -p /usr/share/fonts/liberation-mono
	@sudo cp font/LiberationMono-Regular.ttf \
	/usr/share/fonts/liberation-mono/LiberationMono-Regular.ttf

sys_cmd: $(TARGET)
	@echo "Copying the target in \'/usr/local/bin\'..."
	@sudo cp $(TARGET) /usr/local/bin/$(TARGET)

get_unregistered_files:
	@find src/ -name "*.c" | while read file; do \
        	echo "$(SRC)" | grep -q "$$file" || \
		echo "$$file" >> new_files_detected.txt; \
        done
	@if [ -f new_files_detected.txt ]; then \
                cat new_files_detected.txt | sed "s/src\///g"; \
                rm -f new_files_detected.txt; \
        fi

get_unknow_files:
	@for file in $(SRC); do \
            if [ ! -f "$$file" ]; then \
                echo "$$file" >> missing_files.txt; \
            fi; \
        done;
	@if [ -f missing_files.txt ]; then \
                cat missing_files.txt | sed "s/src\///g"; \
                rm -f missing_files.txt; \
        fi

.PHONY: all lib clean fclean re tests_run sys_cmd set_font \
	get_unregistered_files get_unknow_files
