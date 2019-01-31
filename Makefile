CC = g++

CFLAGS = -Wall -std=c++17 -pthread

WORLD_SOURCES = src/net/sockets/TCPSocket.cpp \
	        src/net/sockets/TCPServerSocket.cpp \
	        src/net/packets/Packet.cpp \
	        src/net/packets/PacketHandler.cpp \
	        src/net/world/worldserver.cpp \
	        src/tools/hexTool.cpp

TOOLS_SOURCES = src/tools/maintools.cpp \
	        src/tools/hexTool.cpp \
		src/net/packets/PacketHandler.cpp \
		src/net/packets/Packet.cpp
	       

OBJECTS=$(SOURCES:.cpp=.o)
	SERVER_EXEC=server
	CLIENT_EXEC=client

all : 
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o worldserver
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools

world :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o worldserver

tools :
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools

clean : 
	rm -f tools
	rm -f worldserver
