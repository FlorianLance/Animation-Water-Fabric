
CFLAGS = -c -g -Wall
#GL_INCLUDE    = -I/usr/include/GL
GL_LIBDIR    = -L. -L/usr/X11R6/lib
#GL_LIBRARIES = -lglut -lGL -lm -lGLU -lXmu -lXext -lXi -lX11
GL_LIBRARIES =  -lglut -lGL -lm -lGLU -lSDL
CC=g++
OS = "unknown"
SRC = SOURCES
OBJ = OBJS

job: clean TP4

TP4: main.o particle.o tissu.o
	$(CC) $(GL_LIBDIR) main.o particle.o tissu.o $(GL_LIBRARIES) -o $@
main.o : main.cpp
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<
tissu.o : tissu.cpp
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<
particle.o : particle.cpp
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

clean:
	rm -rf ./*.o
