PROJECT_DIRECTORY = .

TARGET = emulator
SRC_DIRS = .
INC_DIRS = . 

CC = g++
CC_SDL = -lSDL2 
LD_SDL = 'sdl2-config --libs'

DEPFLAGS = -MP -MD
CPPFLAGS = -g -Wall -O0 -std=c++17 -fdiagnostics-color=always $(foreach D,$(INC_DIRS), -I$(D)) $(DEPFLAGS)




OBJS_DIR = ./obj


SRCS = $(foreach D, $(SRC_DIRS), $(wildcard $(D)/*.cpp))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEPS = $(patsubst %.cpp,%.d,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)	$(CPPFLAGS) -o  $@ $^ $(CC_SDL)

#regular expressions
%.o : %.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CC_SDL) 

clean: 
	rm -rf $(TARGET) $(OBJS) $(DEPS)

#-include $(DEPS)

.PHONY: all clean

