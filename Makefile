CC = g++

CFLAGS = -Wall -g -std=c++14 -pthread

WORLD_SOURCES = src/net/sockets/*.cpp \
		src/net/login/*.cpp \
		src/net/channel/*.cpp \
		src/net/crypto/*.cpp \
		src/net/*.cpp \
	    src/tools/*.cpp \
		src/Master.cpp \
		src/main.cpp

TOOLS_SOURCES = src/maintools.cpp \
	        src/tools/*.cpp \
		src/tools/packets/*.cpp

FILEIO_SOURCES = src/tools/fileIO/*.cpp \
		 src/mainfileIO.cpp

OBJECTS=$(SOURCES:.cpp=.o)
	SERVER_EXEC=server
	CLIENT_EXEC=client

all :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o toolstest
	$(CC) $(CFLAGS) $(FILEIO_SOURCES) -o fileio

master :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master

tools :
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o toolstest

fileio:
	$(CC) $(CFLAGS) $(FILEIO_SOURCES) -o fileio

clean :
	rm -f toolstest
	rm -f fileio
	rm -f master
