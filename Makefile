INCLUDES = -I ./include `sdl2-config --cflags`
FLAGS= -g
LIBS = `sdl2-config --libs` 
all:
	gcc ${FLAGS} ${INCLUDES} ./src/main.c -o ./bin/main ${LIBS}
run:
	./bin/main

clean:
	rm -f ./bin/main
	rm -f ./build/*.o
