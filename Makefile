OS := $(shell uname)

ifeq ($(OS), Darwin)
	CC = g++
	LIBS = -lglfw -framework OpenGL
	CFLAGS =
else ifeq ($(OS), Linux)
	CC = g++
	LIBS = -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread
	CFLAGS = -g -Wall -Wno-deprecated
else
	CC = x86_64-w64-mingw32-g++
#CC = i686-w64-mingw32-g++
#CC = i686-pc-mingw32-g++
	LIBS = -lglfw3 -lopengl32 -lgdi32
#LIBS = -l:glfw3dll.a -lopengl32 -lgdi32
	CFLAGS = -g -Wall -Wno-deprecated
endif

BUILD_DIR := build
TARGET := $(BUILD_DIR)/main
SRC := main.cpp glad.c
OBJ := $(BUILD_DIR)/main.o $(BUILD_DIR)/glad.o

all: $(TARGET)
	@$(TARGET) 

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: FORCE
	-rm -rf $(BUILD_DIR)

FORCE:

