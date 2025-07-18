INCLUDES = -I ./include `sdl2-config --cflags`
FLAGS= -g
LIBS = `sdl2-config --libs` -lm -lpthread
OBJECTS=./build/chip8_memory.o ./build/chip8_stack.o ./build/chip8_keyboard.o ./build/chip8.o ./build/chip8_screen.o ./build/sound.o
all: prepare ${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -o ./bin/main ${LIBS}

./build/chip8_memory.o: ./src/chip8_memory.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_memory.c -c -o ./build/chip8_memory.o

./build/chip8_stack.o: ./src/chip8_stack.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_stack.c -c -o ./build/chip8_stack.o

./build/chip8_keyboard.o: ./src/chip8_keyboard.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_keyboard.c -c -o ./build/chip8_keyboard.o

./build/chip8.o: ./src/chip8.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8.c -c -o ./build/chip8.o

./build/chip8_screen.o: ./src/chip8_screen.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_screen.c -c -o ./build/chip8_screen.o

./build/sound.o: ./src/sound.c
	gcc ${FLAGS} ${INCLUDES} ./src/sound.c -c -o ./build/sound.o
run:
	./bin/main

prepare:
	mkdir -p build bin

clean:
	rm -f ./bin/main
	rm -f ./build/*.o
 