CC=$(shell wx-config --cxx)
CFLAGS=$(shell wx-config --cxxflags --unicode=yes) -Wall #-Wall -pipe -DwxUSE_UNICODE
LDFLAGS=$(shell wx-config --libs core,base)
SOURCES=GanonBeepApp.cpp GanonBeepMain.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES=
EXECUTABLE=bin/Release/GanonBeep

all: dirs $(SOURCES) $(EXECUTABLE)
	cp *.txt bin/Release/

dirs:
	mkdir -p obj/Release/
	mkdir -p bin/Release/

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(INCLUDES) $(addprefix obj/Release/, $(OBJECTS)) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(addprefix obj/Release/, $@)

clean:
	rm -rf obj/**/*.o bin/**/*
