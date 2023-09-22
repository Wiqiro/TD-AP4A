CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++17

SRCS = main.cpp server.cpp
OBJS = $(SRCS:.cpp=.o)

all: server

server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o server

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: server
	./server

clean:
	rm -f $(OBJS) server