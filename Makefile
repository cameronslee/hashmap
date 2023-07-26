CC = gcc
CFLAGS = -Wall -Wextra -std=c99

hashmap: hashmap.o
	$(CC) $(CFLAGS) -o $@ $< hashes.c

hashmap.o: hashmap.c hashes.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f hashmap
