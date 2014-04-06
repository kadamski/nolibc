.PHONY: all

all: nolibc normal

normal: normal.c
	$(CC) $(CFLAGS) -o $@ $^

nolibc: nolibc.c
	$(CC) $(CFLAGS) -nostdlib -o $@ $^
