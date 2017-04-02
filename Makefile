CC= g++
FLAGS= -Ofast -std=c++14 -g -ggdb -Wfatal-errors -w
SFML_LIBS= -lsfml-window -lsfml-graphics -lsfml-system
EXEC_NAME= component_system_test

all: **/*.cpp **/*.hpp
	$(CC) main.cpp **/*.cpp -o $(EXEC_NAME) $(FLAGS) $(SFML_LIBS)


run:
	clear && ./compontent_system_test
