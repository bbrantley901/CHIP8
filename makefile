PROJECT_DIRECTORY = $(shell pwd)
$(info PROJECT_DIRECTORY is $(PROJECT_DIRECTORY))
TARGET = emulator
SRC_DIRS = src
INC_DIRS = inc
OBJS_DIR = obj
CC = g++
CC_SDL = -lSDL2 
DEPFLAGS = -MP -MD
CPPFLAGS = -g -Wall -O0 -std=c++17 -fdiagnostics-color=always $(foreach D,$(INC_DIRS), -I$(D)) $(DEPFLAGS)

#Do not edit below this line 

SRCS = $(foreach D, $(SRC_DIRS), $(wildcard $(D)/*.cpp))
OBJS = $(patsubst $(SRC_DIRS)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
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

