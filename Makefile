CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11

.PHONY: compress clean

# compress target builds boots executable
compress: boots

# boots executable built from compress.c and rle.c inside src/
boots: src/compress.c src/rle.c
	$(CC) $(CFLAGS) -o boots src/compress.c src/rle.c

# Pattern rule: build any other executable from matching .c file in src/
%: src/%.c
	$(CC) $(CFLAGS) -o $@ src/$<
