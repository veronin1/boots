CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11

# make <filename>
%: %.c
	$(CC) $(CFLAGS) -o $@ $<