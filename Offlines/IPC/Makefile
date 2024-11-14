# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -MMD
CXXFLAGS = -Wall -Wextra -MMD
OPTFLAGS = -O2

EXEC = main

# List of all C source files
C_SOURCES = main.c \
util/Id_generator.c

# List of all C++ source files
CXX_SOURCES = util/PoissonRandom.cpp

# Object files derived from C and C++ sources
C_OBJS = $(C_SOURCES:.c=.o)
CXX_OBJS = $(CXX_SOURCES:.cpp=.o)

# All object files
OBJS = $(C_OBJS) $(CXX_OBJS)

.PHONY: all run clean

# The default target (build the executable)
all: $(EXEC)

# Link the executable from object files
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $^

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C++ source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(EXEC).exe $(C_OBJS) $(CXX_OBJS)
else
	rm -f $(EXEC) $(C_OBJS) $(CXX_OBJS)
endif

# Run the executable
run: $(EXEC)
	./$(EXEC)
