#Guilherme Bastos de Oliveira - GRR20167818

CFLAGS = -Wall -fopenmp
LDLIBS = -lSDL -lSDL_gfx
objects = objread.o perspect.o graphics.o

all: wireframe

wireframe: wireframe.o $(objects)
	gcc wireframe.o  -o wireframe $(objects) $(CFLAGS) $(LDLIBS)

wireframe.o: wireframe.c
	gcc -c wireframe.c $(CFLAGS)

objread.o: objread.h objread.c
	gcc -c objread.c $(CFLAGS)

perspect.o: perspect.h perspect.c
	gcc -c perspect.c $(CFLAGS)

graphics.o: graphics.h graphics.c
	gcc -c graphics.c $(CFLAGS)

clean:
	 -rm -f *.o

purge: clean
	rm -f wireframe
