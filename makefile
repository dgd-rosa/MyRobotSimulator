# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++11 -Wall -Iinclude/
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lstdc++


TARGET = robot_sim
TARGET_DEL = robot_sim.exe

# Source file
#SRCS = main.cpp grid/grid.cpp robot/robot.cpp
SRCS := $(shell find ./src -type f -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
