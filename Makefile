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

CFLAGS = -Wall -g -std=c++14 -lpthread
$(info detected os is $(detected_os))
ifeq ($(detected_os), Windows)
	CFLAGS += -Lsrc/lib/cryptopp -lcryptlib
endif

ifeq ($(detected_os), Other)
	CFLAGS += -L/usr/local/lib -l:libcryptopp.a
endif

WORLD_SOURCES = src/net/sockets/*.cpp \
		src/net/login/*.cpp \
		src/net/channel/*.cpp \
		src/net/crypto/*.cpp \
		src/net/*.cpp \
    		src/tools/*.cpp \
		src/Master.cpp \
		src/main.cpp

TOOLS_SOURCES = src/maintools.cpp \
		src/net/crypto/*.cpp \
	        src/tools/*.cpp 


all :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools

master :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master

tools :
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools

clean :
	rm -f tools
	rm -f master
