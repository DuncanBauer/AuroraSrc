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
CFLAGS = -Wall -g -std=c++11 -DSTATIC_CONNPP 
LFLAGS = -lpthread

$(info detected os is $(detected_os))
ifeq ($(detected_os), Windows)
	CFLAGS += -Iincludes
	LFLAGS += -Llib -lcryptopp -llua -lmysqlcppconn8-static -lssl -lcrypto
endif

ifeq ($(detected_os), Other)
	LFLAGS += -lcryptopp -lmysqlcppconn -llua -ldl
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

TOOLS_SOURCES = src/maintools.cpp \
		src/net/crypto/*.cpp \
		src/net/db/*.cpp \
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
