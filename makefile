PROJECT_DIRECTORY = $(shell pwd)
$(info PROJECT_DIRECTORY is $(PROJECT_DIRECTORY))
TARGET = emulator
SRC_DIRS = src
INC_DIRS = inc
OBJS_DIR = obj

CC = g++
CC_SDL = -lSDL2 
LD_SDL = 'sdl2-config --libs'

DEPFLAGS = -MP -MD
CPPFLAGS = -g -Wall -O0 -std=c++17 -fdiagnostics-color=always $(foreach D,$(INC_DIRS), -I$(D)) $(DEPFLAGS)







SRCS = $(foreach D, $(SRC_DIRS), $(wildcard $(D)/*.cpp))
$(info SRCS is $(SRCS))
OBJS = $(patsubst $(SRC_DIRS)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
$(info OBJS is $(OBJS))
DEPS = $(patsubst $(SRC_DIRS)/%.cpp,$(OBJS_DIR)/%.d,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)	$(CPPFLAGS) -o  $@ $^ $(CC_SDL)

#regular expressions
$(OBJS_DIR)/%.o : $(SRC_DIRS)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CC_SDL) 

clean: 
	rm -rf $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

.PHONY: all clean 

