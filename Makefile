PROGRAM = projekat
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm -Wall

$(PROGRAM): main.o mete.o 
	$(CC) $(LDFLAGS) -o $(PROGRAM) $^ $(LDLIBS)


main.o: main.c mete.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)

mete.o: mete.c mete.h 
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)


.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
