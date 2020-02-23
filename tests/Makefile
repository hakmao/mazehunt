TARGET_EXE = mazehunt

SRC_DIR := ./src
INC_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./bin
DEMO_DIR := ./demos
TEST_DIR := ./tests
TEST_BUILD := ./tests

SRC_FILES := $(shell find $(SRC_DIR) -name *.cpp)
TEST_FILES := $(shell find $(TEST_DIR) -name *.cpp)
DEMO_FILES := $(shell find $(DEMO_DIR) -name *.cpp)

OBJ_FILES := $(SRC_FILES:%=$(BUILD_DIR)/%.o)

CXX = g++
LINKER = g++
INC_FLAGS := $(addprefix -I, $(INC_DIR))
CXX_STD := -std=c++17
CXX_FLAGS = $(INC_FLAGS) $(CXX_STD)
LD_FLAGS= -lncurses

MKDIR_P := mkdir -p

.PHONY: all tests demos clean clean_tests clean_demos

all: $(BIN_DIR)/$(TARGET_EXE)

$(BIN_DIR)/$(TARGET_EXE): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) $(CXX_STD) $(OBJ_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

### Tests ###

# Run tests
#$(BUILD_DIR)/all_tests: all_tests.o maze.o
#	$(CPP) $(CPP_FLAGS) $^ -o $@
#
#all_tests.o: all_tests.cpp
#	$(CPP) $(CPP_FLAGS) -c $<

# Search
$(BIN_DIR)/search_tests: $(BUILD_DIR)/search_tests.o $(BUILD_DIR)/search.o $(BUILD_DIR)/grid.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(BUILD_DIR)/search_tests.o: $(TEST_DIR)/search_tests.cpp
	$(CPP) $(CPP_FLAGS) -c $<

# Maze
$(TEST_DIR)/maze_tests: $(TEST_DIR)/maze_tests.o maze.o utils.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(TEST_DIR)/maze_tests.o: $(TEST_DIR)/maze_tests.cpp
	$(CPP) $(CPP_FLAGS) -c $<

# Grid
$(TEST_DIR)/grid_tests: $(TEST_DIR)/grid_tests.o grid.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(TEST_DIR)/grid_tests.o: $(TEST_DIR)/grid_tests.cpp
	$(CPP) $(CPP_FLAGS) -c $<

# View
$(TEST_DIR)/gameview_test: $(TEST_DIR)/gameview_test.o gameview.o grid.o
	$(CPP) $(LDFLAGS) $(CPP_FLAGS) $^ -o $@

$(TEST_DIR)/gameview_test.o: $(TEST_DIR)/gameview_test.cpp
	$(CPP) $(CPP_FLAGS) -c $<

### Demos ###
$(BIN_DIR)/maze_demo: $(BUILD_DIR)/maze_demo.o $(BUILD_DIR)/maze.o $(BUILD_DIR)/utils.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(DEMO_DIR)/maze_demo.o: $(DEMO_DIR)/maze_demo.cpp
	$(CPP) $(CPP_FLAGS) -c $<

$(DEMO_DIR)/grid_demo: $(DEMO_DIR)/grid_demo.o grid.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(DEMO_DIR)/grid_demo.o: $(DEMO_DIR)/grid_demo.cpp
	$(CPP) $(CPP_FLAGS) -c $<

search_demo: $(DEMO_DIR)/search_demo

$(DEMO_DIR)/search_demo: $(DEMO_DIR)/search_demo.o search.o grid.o
	$(CPP) $(CPP_FLAGS) $^ -o $@

$(DEMO_DIR)/search_demo.o: $(DEMO_DIR)/search_demo.cpp
	$(CPP) $(CPP_FLAGS) -c $<

### Clean up ###

clean:
	@echo "Cleaning up..."
	rm -rvf $(BUILD_DIR)
	clean_tests
	clean_demos

clean_tests:
	rm $(TEST_DIR)/*_tests $(TEST_DIR)/*.o

clean_demos:
	rm $(DEMO_DIR)/*_tests $(DEMO_DIR)/*.o
