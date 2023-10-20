CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp server.cpp scheduler.cpp sensors/sensor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=myserver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)