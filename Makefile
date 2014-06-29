CFLAGS = -g -Wall -pedantic -ansi -Wno-unused-result -D _BSD_SOURCE -O2
LFLAGS = -lglut -lGLEW -lGL -lGLU -lm
CC = gcc

light.out: light.c gllight.o
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

gllight.o: gllight.c
	$(CC) $(CFLAGS) $^ -c -o $@
