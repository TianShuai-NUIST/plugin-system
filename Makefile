CC := clang
BUILD_DIR := build
TEST_DIR := test
TARGET := $(BUILD_DIR)/program

MODE ?= debug

# SRC := src/main.c \
#        src/plugin_vector.c \
#        src/utils.c
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

CFLAGS := -Wall -Wextra -Iinclude
DEPFLAGS := -MMD -MP
LDLIBS := -ldl

ifeq ($(MODE), debug)
	CFLAGS += -g -pg -O0 -DDEBUG
else
	CFLAGS += -g1 -O2
endif

PLUGIN_TYPE := plugin
PLUGIN_SRC := $(wildcard src/plugin/*.c)
PLUGIN_SO := $(patsubst src/plugin/%.c, plugin/%.$(PLUGIN_TYPE), $(PLUGIN_SRC))

.PHONY: all clean run tags test

all: $(TARGET) $(PLUGIN_SO)

plugin/%.$(PLUGIN_TYPE): src/plugin/%.c
	@mkdir -p plugin
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ -pg $(LDLIBS)

clean:
	rm -rf $(BUILD_DIR) plugin/*.$(PLUGIN_TYPE)

run: $(TARGET) $(PLUGIN_SO)
	@cd $(BUILD_DIR) && ./program ../plugin

test: $(TARGET)
	$(CC) $(CFLAGS) -Itest test/test_types.c src/types.c src/utils.c -o $(BUILD_DIR)/test_types
	@./$(BUILD_DIR)/test_types


SRCS    := $(shell find . -name '*.c' -not -path './.git/*' | grep -v build)
tags:
	ctags -f .ctags -R .
	@printf '%s\n' "$(SRCS)" | xargs gcc -M 2>/dev/null | tr ' \\' '\n' | grep '\.h$$' \
		| grep -v "$(CURDIR)/" | grep -vE '/(bits|sys|asm|gnu)/' | sort -u \
		| xargs ctags --quiet --c++-kinds=+p -f .tags.sys
	@echo "tags 生成完毕: $$(wc -l < .ctags) + $$(wc -l < .tags.sys)"

-include $(OBJ:.o=.d)
