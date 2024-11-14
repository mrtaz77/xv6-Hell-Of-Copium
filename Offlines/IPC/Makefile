# Makefile for separate C compilation
# Requires GNU Make.

CC = gcc
CFLAGS = -Wall -Wextra -MMD
OPTFLAGS = -O2

EXEC = main

# List of all C source files
C_SOURCES = main.c \
util/Id_generator.c \
util/util.c

# Object files derived from C sources
OBJS = $(C_SOURCES:.c=.o)

# Dependency files for each object file
DEPS = $(OBJS:.o=.d)

.PHONY: all run clean

all: $(EXEC)

# Linking executable from object files
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $@ $^

# Compiling .c files to .o files, generating .d dependency files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(EXEC).exe $(OBJS) $(DEPS)
else
	rm -f $(EXEC) $(OBJS) $(DEPS)
endif

# Run the executable
run: $(EXEC)
	./$(EXEC)

# Include dependency files
-include $(DEPS)
