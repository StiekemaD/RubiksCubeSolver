EXECUTABLE=rubikscube

CC=g++
CFLAGS=-std=c++17 -g
LDFLAGS=-pthread -lsfml-graphics -lsfml-window -lsfml-system

DEPS=$(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(DEPS) 
	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAGS) 

.PHONY: clean build rebuild

clean: 
	-rm -rf $(OBJECTS) $(EXECUTABLE)

rebuild: clean build

