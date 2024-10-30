SOURCES := ./src/main.cpp ./src/graph.cpp ./src/board.cpp ./src/ui.cpp

make : $(SOURCES)
	g++ -g -Wall -o a.exe $(SOURCES)