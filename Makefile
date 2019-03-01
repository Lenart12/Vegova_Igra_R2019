CXX      := -c++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-narrowing
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lSDL2_image -lSDL2 -lpthread
BUILD    := ./Build
OBJ_DIR  := $(BUILD)/Objects
APP_DIR  := $(BUILD)/Apps
TARGET   := Igrica
INCLUDE  := -IInclude/ -I/usr/include/SDL2
SRC      := $(wildcard Src/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(APP_DIR)/$(TARGET) $(INCLUDE) $(LDFLAGS)

.PHONY: all build clean debug release windows

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

windows: LDFLAGS += -lmingw32 -lSDL2main -lSDL2 -mwindows

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
                       