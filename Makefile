CC= g++
FLAGS= -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w
SFML_LIBS= -lsfml-window -lsfml-graphics -lsfml-system
EXEC_NAME= component_system_test

all: **/*.hpp **/*.cpp
	$(CC) main.cpp **/*.cpp -o $(EXEC_NAME) $(FLAGS) $(SFML_LIBS)

run:
	clear && ./compontent_system_test

# 
# BIN = bin
# SRC = src
# INC = include
# LIBS = -lsfml-graphics -lsfml-window -lsfml-system
# FLAGS = -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w
# OBJ = $(BIN)/*.o
# TARGET = $(BIN)/game
# CC = g++
# DEPS = $(patsubst %, $(BIN)/%, $(OBJ))
#
# default: $(TARGET)
#
# $(BIN)/%.o: $(SRC)/%.cpp
# 	$(CC) $(FLAGS) -I$(INC) -c $^ -o $@
#
# $(TARGET): $(DEPS)
# 	$(CC) $(DEPS) $(LIBS) $(FLAGS) -o $@
#
# .PHONY: clean
# clean:
# 	-rm -f $(DEPS) $(BIN)/$(TARGET)
