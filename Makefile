CXX = g++
CXXFLAGS = -c -std=c++17 
LDFLAGS=-lncurses -Wall -std=c++17
EXE = mazehunt
OBJECTS = main.o game.o display.o grid.o cell.o utils.o 

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJECTS)

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

game.o: game.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

display.o: display.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

grid.o: grid.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

cell.o: cell.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

utils.o: utils.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm *.o $(EXE)
