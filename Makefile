CXX = g++
CXXFLAGS = -c -std=c++17 
LDFLAGS=-lncurses -Wall -std=c++17
EXE = mazehunt
OBJECTS = main.o input_parser.o game.o display.o maze.o node.o utils.o 

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJECTS)

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

input_parser.o: input_parser.cpp
	$(CXX) $(CXXFLAGS) -c $<

game.o: game.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

display.o: display.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

maze.o: maze.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

node.o: node.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

utils.o: utils.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm *.o $(EXE)
