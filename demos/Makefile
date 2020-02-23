SRC_DIR := ../src
DEMO_DIR := ./src
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

#all: $(BIN_DIR)/$(TARGET_EXE)

#$(BIN_DIR)/$(TARGET_EXE): $(OBJ_FILES)
#	$(CXX) $(LD_FLAGS) $(CXX_STD) $(OBJ_FILES) -o $@
#
#$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
#	$(MKDIR_P) $(dir $@)
#	$(CXX) $(CXX_FLAGS) -c $< -o $@
### All ###

all: maze_demo grid_demo search_demo

## Demos ###
maze_demo: $(BUILD_DIR)/maze_demo.o $(BUILD_DIR)/maze.o $(BUILD_DIR)/utils.o
	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

grid_demo: $(BUILD_DIR)/grid_demo.o $(BUILD_DIR)/grid.o
	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

search_demo: $(BUILD_DIR)/search_demo.o $(BUILD_DIR)/search.o $(BUILD_DIR)/grid.o
	$(LINKER) $(CXX_FLAGS) $(LD_FLAGS) $^ -o $@

### Objects ###
$(BUILD_DIR)/maze_demo.o: $(DEMO_DIR)/maze_demo.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/grid_demo.o: $(DEMO_DIR)/grid_demo.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/search_demo.o: $(DEMO_DIR)/search_demo.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

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
	rm ./*_demo ./*.grid

