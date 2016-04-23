CC = gcc
CFLAGS = -g -Wall -Werror -lm -lSOIL -lGL -lGLU -lglut
TARGET = prettyScene

default: prettyScene

prettyScene: prettyScene.o ezloader.o
	$(CC) -o prettyScene prettyScene.o ezloader.o $(CFLAGS)

prettyScene.o: prettyScene.c ezloader.h
	$(CC) -c prettyScene.c $(CFLAGS)

ezloader.o: ezloader.c ezloader.h
	$(CC) -c ezloader.c $(CFLAGS)

clean:
	$(RM) ezloader *.o *~
