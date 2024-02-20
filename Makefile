# Compiler
CC=g++

# Compiler flags
CFLAGS=-Wall -g -std=c++11 `pkg-config --cflags freetype2`

# Libraries
LIBS=`pkg-config --libs freetype2` -lglfw -lGLU -lGL -lGLEW

# Source files
SRCS=Bunny.cpp Camera.cpp Container.cpp Containers.cpp Game.cpp GameObject.cpp Ground.cpp HUD.cpp Mesh.cpp Shader.cpp main.cpp

# Object files (convert .cpp files to .o)
OBJS=$(SRCS:.cpp=.o)

# Executable name
EXECUTABLE=main

# Default target
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target for removing compiled files
clean:
	rm -f $(OBJS) $(EXECUTABLE)
