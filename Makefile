CC=g++
CFLAGS=$(shell wx-config --cppflags) #-Wall -pipe -DwxUSE_UNICODE
LDFLAGS=-mthreads
SOURCES=GanonBeepApp.cpp GanonBeepMain.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES=
EXECUTABLE=bin/Release/GanonBeep

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(INCLUDES) $(addprefix obj/Release/, $(OBJECTS)) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $(addprefix obj/Release/, $@)

clean:
	rm -rf obj/**/*.o bin/**/*
