TARGET_EXE = mazehunt

SRC_DIR := ./src
INC_DIR := ./include
BUILD_DIR := ./build

SRC_FILES := $(shell find $(SRC_DIR) -name *.cpp)
OBJ_FILES := $(SRC_FILES:%=$(BUILD_DIR)/%.o)

CXX = g++
LINKER = g++
INC_FLAGS := $(addprefix -I, $(INC_DIR))
CXX_STD := -std=c++17
CXX_FLAGS = $(INC_FLAGS) $(CXX_STD)
LD_FLAGS= -lncurses -pthread

MKDIR_P := mkdir -p

.PHONY: all

all: $(TARGET_EXE)

$(TARGET_EXE): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) $(CXX_STD) $(OBJ_FILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

### Clean up ###

clean:
	@echo "Cleaning up..."
	rm -rvf $(BUILD_DIR)
	$(MKDIR_P) $(BUILD_DIR)


