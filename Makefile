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
CFLAGS = -Wall -g -std=c++14 -pthread
LFLAGS =

$(info detected os is $(detected_os))
ifeq ($(detected_os), Windows)
	CFLAGS += -I includes
	LFLAGS += -L lib -l cryptopp -l mysqlcppconn8-static -l lua
endif

ifeq ($(detected_os), Other)
	LFLAGS += -l cryptopp -l mysqlcppconn
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
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master $(LFLAGS)
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools $(LFLAGS)

master :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -o master $(LFLAGS)

tools :
	$(CC) $(CFLAGS) $(TOOLS_SOURCES) -o tools $(LFLAGS)

clean :
	rm -f tools master
