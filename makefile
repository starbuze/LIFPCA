CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 
IMGUI_SRC_DIR = imgui
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
LIBS_IMGUI = -I$(IMGUI_SRC_DIR)
LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lncurses  

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
IMGUI_SRCS := $(wildcard $(IMGUI_SRC_DIR)/*.cpp) 
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
IMGUI_OBJS := $(IMGUI_SRCS:$(IMGUI_SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

EXECUTABLE = $(BIN_DIR)/programme

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(IMGUI_OBJS) $(OBJS) 
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS_IMGUI) $(LIBS_SDL) 


-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@ $(LIBS_IMGUI) $(LIBS_SDL) 

$(BUILD_DIR)/%.o: $(IMGUI_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@ $(LIBS_IMGUI) $(LIBS_SDL) 
	
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
