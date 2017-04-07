# General settings
BIN = bin
SRC = src
INC = include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w -fPIC
OBJ = Entity.o Component.o TestComponents.o Event.o
MAIN = main.o
OBJ := $(OBJ) $(MAIN)
TARGET := $(BIN)/BabyECS
CC = g++
DEPS = $(patsubst %, $(BIN)/%,$(OBJ))
STATIC_DEPS = $(filter-out $(BIN)/$(MAIN),$(DEPS))

# Macro's for project directories
__ROOT_DIR__= -D__ROOT_DIR__=\(std::string\)\"$(shell pwd)\"
__SRC_DIR__= -D__SRC_DIR__=__ROOT_DIR__+\"/src\"
__INCLUDE_DIR__= -D__INCLUDE_DIR__=__ROOT_DIR__+\"/include\"
__TEST_DIR__= -D__TEST_DIR__=__ROOT_DIR__+\"/test\"
DIR_MACROS= $(__ROOT_DIR__) $(__SRC_DIR__) $(__INCLUDE_DIR__) $(__TEST_DIR__)

default: $(TARGET)
static: $(TARGET).a

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) $(DIR_MACROS) -I$(INC) -c $^ -o $@

$(BIN)/%.o: $(SRC)/**/%.cpp
	$(CC) $(FLAGS) -I$(INC) -c $^ -o $@

$(TARGET): $(DEPS)
	$(CC) $(DEPS) $(LIBS) $(FLAGS) -o $@

$(TARGET).a: $(STATIC_DEPS)
	ld -r $(STATIC_DEPS) -o $(TARGET).o
	ar rvs $(TARGET).a $(TARGET).o
	-rm $(TARGET).o

.PHONY: clean run
clean:
	-rm -f $(DEPS) $(TARGET) $(TARGET).a

run:
	./$(TARGET)
