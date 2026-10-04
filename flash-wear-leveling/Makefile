
CC = gcc
CFLAGS = -Wall -Iinclude

wear_leveling:
	$(CC) $(CFLAGS) src/main.c src/flash.c src/wear_leveling.c -o wear_leveling

clean:
	rm -f wear_leveling
