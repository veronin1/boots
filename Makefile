CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11

.PHONY: compress clean

# Phony target: 'make compress' builds the 'boots' executable from compress.c
compress: boots

# boots executable built from compress.c
boots: compress.c
	$(CC) $(CFLAGS) -o boots compress.c

# Pattern rule: build any other executable from matching .c file
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

