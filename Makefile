CC = g++

CFLAGS = -Wall -g -std=c++14 -pthread

WORLD_SOURCES = src/net/sockets/*.cpp \
		src/net/login/*.cpp \
		src/net/channel/*.cpp \
		src/net/crypto/*.cpp \
		src/net/*.cpp \
		src/client/*.cpp \
	        src/tools/*.cpp \
		src/tools/packets/*.cpp \
		src/Master.cpp \
		src/main.cpp

TOOLS_SOURCES = src/maintools.cpp \
	        src/tools/*.cpp \
		src/tools/packets/*.cpp \
	       

OBJECTS=$(SOURCES:.cpp=.o)
	SERVER_EXEC=server
	CLIENT_EXEC=client

all : 
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o toolstest

master :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master

tools :
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o toolstest

clean : 
	rm -f toolstest
	rm -f master
