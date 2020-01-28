CXX = g++
CXXFLAGS = -std=c++17 
LDFLAGS= -lncurses 
EXE = mazehunt
OBJECTS = main.o input_parser.o game.o display.o maze.o node.o utils.o 

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(EXE) $(OBJECTS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< 

input_parser.o: input_parser.cpp
	$(CXX) $(CXXFLAGS) -c $<

game.o: game.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

display.o: display.cpp 
	$(CXX) $(CXXFLAGS) -c $<

grid.o: grid.cpp
	$(CXX) $(CXXFLAGS) -c $<

gameview.o: gameview.cpp
	$(CXX) $(CXXFLAGS) -c $<

maze.o: maze.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

node.o: node.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

utils.o: utils.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

search.o: search.cpp
	$(CXX) $(CXXFLAGS) -c $<

### Tests ###

# Run tests
run_tests: run_tests.o maze.o
	$(CXX) $(CXXFLAGS) $^ -o $@

run_tests.o: run_tests.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Search
search_test: search_test.o search.o grid.o
	$(CXX) $(CXXFLAGS) $^ -o $@

search_test.o: search_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Maze
maze_tests: maze_tests.o maze.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@

maze_tests.o: maze_tests.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Grid
grid_tests: grid_tests.o grid.o
	$(CXX) $(CXXFLAGS) $^ -o $@

grid_tests.o: grid_tests.cpp
	$(CXX) $(CXXFLAGS) -c $<

# View
gameview_test: gameview_test.o gameview.o grid.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $^ -o $@

gameview_test.o: gameview_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

### Demos ###
maze_demo: maze_demo.o maze.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@

maze_demo.o: maze_demo.cpp
	$(CXX) $(CXXFLAGS) -c $<

grid_demo: grid_demo.o grid.o
	$(CXX) $(CXXFLAGS) $^ -o $@

grid_demo.o: grid_demo.cpp
	$(CXX) $(CXXFLAGS) -c $<

### Clean up ###
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm *.o $(EXE) *_test
