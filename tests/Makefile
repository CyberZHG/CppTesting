.PHONY: all

CFLAGS=-Wall -Wextra -Weffc++ -Werror -g -std=c++11 -fprofile-arcs -ftest-coverage
MACRO=-D_U_S_TEST

OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard *.cpp) $(wildcard ../src/*.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS_PATH = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(wildcard ../src/*.cpp)))
TARGETS = $(patsubst %.cpp, %, $(basename $(wildcard *.cpp)))

%.o: %.cpp
	$(CXX) -I../include $(CFLAGS) $(MACRO) -c $< -o $(OBJ_DIR)/$(notdir $@)

pre-build:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

all: $(TARGETS)

$(TARGETS): %: $(OBJS)
	$(CXX) $(OBJS_PATH) $(OBJ_DIR)/$@.o -o $(BIN_DIR)/$@ --coverage

clean:
	rm -rf obj bin
