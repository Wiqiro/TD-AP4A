CC=g++
CFLAGS=-c -Wall -pedantic -std=c++17
SOURCES=main.cpp server.cpp scheduler.cpp sensors/humidity.cpp sensors/light.cpp sensors/sound.cpp sensors/temperature.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=iot_simulator
LOGS= logs

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(LOGS)