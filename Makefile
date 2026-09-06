CC := clang
TARGET := ./build/program
BUILD := build
# SRC := src/main.c \
#        src/plugin_vector.c \
#        src/utils.c
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
CFLAGS := -Wall -Wextra -pg -g -Iinclude
DEPFLAGS := -MMD -MP
LDLIBS := -ldl
PLUGIN_SRC := $(wildcard src/plugin/*.c)
PLUGIN_SO := $(patsubst src/plugin/%.c, plugin/lib%.so, $(PLUGIN_SRC))

.PHONY: all clean run tags

all: $(TARGET) $(PLUGIN_SO)

plugin/lib%.so: src/plugin/%.c
	@mkdir -p plugin
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

$(BUILD)/%.o: src/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ -pg $(LDLIBS)

clean:
	rm -rf $(BUILD) plugin/*.so

run: $(TARGET) $(PLUGIN_SO)
	@cd $(BUILD) && ./program ../plugin

SRCS    := $(shell find . -name '*.c' -not -path './.git/*' | grep -v build)
tags:
	ctags -f .ctags -R .
	@printf '%s\n' "$(SRCS)" | xargs gcc -M 2>/dev/null | tr ' \\' '\n' | grep '\.h$$' \
		| grep -v "$(CURDIR)/" | grep -vE '/(bits|sys|asm|gnu)/' | sort -u \
		| xargs ctags --quiet --c++-kinds=+p -f .tags.sys
	@echo "tags 生成完毕: $$(wc -l < .ctags) + $$(wc -l < .tags.sys)"

-include $(OBJ:.o=.d)
