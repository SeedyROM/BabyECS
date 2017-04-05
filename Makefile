# General settings
BIN = bin
SRC = src
INC = include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w -fPIC
OBJ = Entity.o Component.o TestComponents.o
MAIN = main.o
OBJ := $(OBJ) $(MAIN)
TARGET := $(BIN)/BabyECS
CC = g++
DEPS = $(patsubst %, $(BIN)/%,$(OBJ))
SHARED_DEPS = $(filter-out $(BIN)/$(MAIN),$(DEPS))

# Macro's for project directories
__ROOT_DIR__= -D__ROOT_DIR__=\(std::string\)\"$(shell pwd)\"
__SRC_DIR__= -D__SRC_DIR__=__ROOT_DIR__+\"/src\"
__INCLUDE_DIR__= -D__INCLUDE_DIR__=__ROOT_DIR__+\"/include\"
__TEST_DIR__= -D__TEST_DIR__=__ROOT_DIR__+\"/test\"
DIR_MACROS= $(__ROOT_DIR__) $(__SRC_DIR__) $(__INCLUDE_DIR__) $(__TEST_DIR__)

default: $(TARGET)
shared: $(TARGET).so

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(FLAGS) $(DIR_MACROS) -I$(INC) -c $^ -o $@

$(BIN)/%.o: $(SRC)/**/%.cpp
	$(CC) $(FLAGS) $(DIR_MACROS) -I$(INC) -c $^ -o $@

$(TARGET): $(DEPS)
	$(CC) $(DEPS) $(LIBS) $(FLAGS) -o $@

$(TARGET).so: $(SHARED_DEPS)
	@echo $(SHARED_DEPS)
	$(CC) $(SHARED_DEPS) $(LIBS) $(FLAGS) -shared -o $@

.PHONY: clean run
clean:
	-rm -f $(DEPS) $(BIN)/$(TARGET) $(BIN)/$(TARGET).so

run:
	./$(TARGET)
