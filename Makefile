CC=g++
CFLAGS=-c -Wall `pkg-config --cflags gl` -g -DGL_GLEXT_PROTOTYPES -DGL_FRAGMENT_PRECISION_HIGH -std=c++11
LDFLAGS=-lGL -lncurses -lX11
SOURCES=main.cpp context_glx.cpp shader.cpp renderer.cpp display.cpp objloader.cpp apirunner/game.cpp apirunner/player.cpp apirunner/gamecube.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=n3

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *~ *.o n3

