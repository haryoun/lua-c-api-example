CC = gcc
CFLAGS = -I/usr/include/lua5.1
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -llua5.1

run: run.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm run
