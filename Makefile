ifeq ($(OS),Windows_NT)
	detected_os := Windows
else
	detected_os := Other
#	detected_os := $(shell uname  2>/dev/null || echo Unknown)
#	detected_os := $(patsubst,CYGWI,$(detected_os))
#	detected_os := $(patsubst MSYS%,MSYS,$(detected_os))
#	detected_os := $(patsubst MINGW%,MSYS,$(detected_os))
endif



CC = g++
CFLAGS = -Wall -g -std=c++14 -DSTATIC_CONCPP
LFLAGS =

$(info detected os is $(detected_os))
ifeq ($(detected_os), Windows)
	CFLAGS += -Iincludes
	LFLAGS += -Llib -llua -lcryptopp -lssl -ldl -lcrypto -lws2_32 -lpthread
endif

ifeq ($(detected_os), Other)
	LFLAGS += -llua -lcryptopp -lmysqlcppconn -ldl -lpthread
endif



WORLD_SOURCES = src/net/sockets/*.cpp \
		src/net/login/*.cpp \
		src/net/channel/*.cpp \
		src/net/crypto/*.cpp \
		src/net/db/*.cpp \
		src/net/*.cpp \
		src/tools/*.cpp \
		src/Master.cpp \
		src/main.cpp

TOOLS_WINDOWS = src/maintools.cpp \
		src/net/crypto/*.cpp \
		src/tools/*.cpp \
		src/net/sockets/TCPSocketWindows.cpp \
		src/Master.cpp

TOOLS_LINUX =   src/maintools.cpp \
		src/net/crypto/*.cpp \
		src/tools/*.cpp \
		src/net/sockets/TCPSocket.cpp \
		src/Master.cpp


all :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master $(LFLAGS)
	$(CC) $(CFLAGS) $(TOOLS_WINDOWS) -o wintools $(LFLAGS)
	$(CC) $(CFLAGS) $(TOOLS_LINUX) -o lintools $(LFLAGS)

master :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master $(LFLAGS)

wintools :
	$(CC) $(CFLAGS) $(TOOLS_WINDOWS) -o wintools $(LFLAGS)
lintools :
	$(CC) $(CFLAGS) $(TOOLS_LINUX) -o lintools $(LFLAGS)

clean :
	rm -f master lintools wintools
