CC=g++
CFLAGS=-c -Wall -pedantic -std=c++17
LDFLAGS=
SOURCES=main.cpp server.cpp scheduler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=iot_simulator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)