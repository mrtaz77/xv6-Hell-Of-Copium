# This Makefile is designed for separate compilation.
# It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -MMD

EXEC = main

# List of all source files
CPP_SOURCES = main.cpp \
classes/random-number-generator/PoissonRandom.cpp \
classes/ticket-generator/TicketGenerator.cpp \
classes/util/Util.cpp \
classes/visitor/Visitor.cpp

CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

OBJS_WIN = $(subst /,\,$(OBJS))

DEPS = $(CPP_SOURCES:.cpp=.d)

.PHONY: all run clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(EXEC).exe) $(OBJS_WIN) $(DEPS)
else 
	rm -f $(EXEC) $(OBJS) $(DEPS)
endif

run: $(EXEC)
	./$(EXEC) $(ARGS)

# Include dependency files
-include $(DEPS) 
