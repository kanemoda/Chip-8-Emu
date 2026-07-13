CC = gcc

CFLAGS = -Wall -g -MMD
INCLUDES = -I ./include 
LIBS = -lSDL2

TARGET = ./bin/main

SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(SOURCES:./src/%.c=./build/%.o)

DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean run

-include $(DEPS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p ./bin
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

./build/%.o: ./src/%.c
	mkdir -p ./build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf ./build ./bin

run: $(TARGET)
	@./$(TARGET)