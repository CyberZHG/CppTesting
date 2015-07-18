CC=g++
INC=-I./include
CFLAGS=-Wall -O -g -std=c++11

OBJ_DIR = obj
BIN_DIR = bin
TARGET = test

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $(OBJ_DIR)/$(notdir $@)

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS_PATH = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))

$(TARGET): pre-build $(OBJS)
	$(CC) $(OBJS_PATH) $(INC) -o $(BIN_DIR)/$(TARGET)

pre-build:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf obj bin

