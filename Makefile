CC = gcc
CFLAGS = -g -Wall


test_map: test_map.c cmap.c hash.c
	gcc -o test_map test_map.c cmap.c hash.c -I.

clean:
	$(RM) test_map
