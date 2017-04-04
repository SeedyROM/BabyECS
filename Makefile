# General settings
BIN = bin
SRC = src
INC = include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w
OBJ = Entity.o Component.o TestComponents.o main.o
TARGET = $(BIN)/BabyECS
CC = g++
DEPS = $(patsubst %, $(BIN)/%, $(OBJ))

# Macro's for project directories
__ROOT_DIR__= -D__ROOT_DIR__=\(std::string\)\"$(shell pwd)\"
__SRC_DIR__= -D__SRC_DIR__=__ROOT_DIR__+\"/src\"
__INCLUDE_DIR__= -D__INCLUDE_DIR__=__ROOT_DIR__+\"/include\"
__TEST_DIR__= -D__TEST_DIR__=__ROOT_DIR__+\"/test\"
DIR_MACROS= $(__ROOT_DIR__) $(__SRC_DIR__) $(__INCLUDE_DIR__) $(__TEST_DIR__)

default: $(TARGET)

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) -I$(INC) -c $^ -o $@

$(BIN)/%.o: $(SRC)/**/%.cpp
	$(CC) $(FLAGS) -I$(INC) -c $^ -o $@

$(TARGET): $(DEPS)
	$(CC) $(DEPS) $(LIBS) $(FLAGS) -o $@

.PHONY: clean run
clean:
	-rm -f $(DEPS) $(BIN)/$(TARGET)

run:
	./$(TARGET)
