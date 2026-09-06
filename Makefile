CC := clang
SRC := main.c
LIB_FILE := add.c
LIB_FOLDER := ./plugin
TARGET := program
CFLAG := -Wall -pg -g -lc -Wextra -ldl

SRCS    := $(shell find . -name '*.c' -not -path './.git/*' | grep -v build)

lib: $(SRC)
	$(CC) -shared -fPIC $(LIB_FILE) -o ${LIB_FOLDER}/libadd.so

$(TARGET): $(SRC) lib
	$(CC) $(SRC) -o $(TARGET) $(CFLAG)

tags:
	ctags -f .ctags -R .
	@printf '%s\n' "$(SRCS)" | xargs gcc -M 2>/dev/null | tr ' \\' '\n' | grep '\.h$$' \
		| grep -v "$(CURDIR)/" | grep -vE '/(bits|sys|asm|gnu)/' | sort -u \
		| xargs ctags --quiet --c++-kinds=+p -f .tags.sys
	@echo "tags 生成完毕: $$(wc -l < .ctags) + $$(wc -l < .tags.sys)"

clean:
	-rm -f *.o ${TARGET}

run: ${TARGET}
	@./${TARGET} Makefile
