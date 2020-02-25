SRC_DIR := ../src
TEST_DIR := ./src
INC_DIR1 := ../include
BUILD_DIR := ./build

SRC_FILES := $(shell find $(SRC_DIR) -name *.cpp)
#OBJ_FILES := $(SRC_FILES:%=$(BUILD_DIR)/%.o)

CXX = g++
LINKER = g++
INC_FLAGS := $(addprefix -I, $(INC_DIR1))
CXX_STD := -std=c++17
CXX_FLAGS = $(INC_FLAGS) $(CXX_STD)
LD_FLAGS= -lncurses

MKDIR_P ?= mkdir -p

.PHONY: all clean


### Tests ###
all: grid_tests maze_tests #search_tests #gameview_tests

# Search
#search_tests: $(BUILD_DIR)/search_tests.o $(BUILD_DIR)/search.o $(BUILD_DIR)/grid.o
#	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

# Maze
maze_tests: $(BUILD_DIR)/maze_tests.o $(BUILD_DIR)/maze.o $(BUILD_DIR)/utils.o
	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

# Grid
grid_tests: $(BUILD_DIR)/grid_tests.o $(BUILD_DIR)/grid.o
	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

# View
#gameview_tests: $(TEST_DIR)/gameview_tests.o $(BUILD_DIR)/gameview.o $(BUILD_DIR)/grid.o
#	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

### Object files ###
#$(BUILD_DIR)/search_tests.o: $(TEST_DIR)/search_tests.cpp
#	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/maze_tests.o: $(TEST_DIR)/maze_tests.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/grid_tests.o: $(TEST_DIR)/grid_tests.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

#$(BUILD_DIR)/gameview_test.o: $(TEST_DIR)/gameview_tests.cpp
#	$(CXX) $(CXX_FLAGS) -c $< $@

$(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/maze.o: $(SRC_DIR)/maze.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/grid.o: $(SRC_DIR)/grid.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/search.o: $(SRC_DIR)/search.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

### Clean up ###
clean:
	@echo "Cleaning up..."
	rm -rvf $(BUILD_DIR)
	$(MKDIR_P) $(BUILD_DIR)
	rm ./*_tests ./*.grid

