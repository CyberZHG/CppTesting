CC=g++
INC=-I./include
CFLAGS=-Wall -O -g -std=c++11

BIN_DIR = bin
TARGET = test

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS_PATH = $(patsubst %.cpp, %.o, $(SOURCES))

$(TARGET): pre-build $(OBJS)
	$(CC) $(OBJS_PATH) $(INC) -o $(BIN_DIR)/$(TARGET)

pre-build:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf obj bin

