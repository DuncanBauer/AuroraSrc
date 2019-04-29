#ifeq '$(findstring ;,$(PATH))' ';'
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
$(info detected os is $(detected_os))
ifeq ($(detected_os), Windows)
	#CFLAGS += -L. -lsrc/lib/cryptopp/x64/Output/Release/cryptlib
	CFLAGS += -L. -lsrc/lib/cryptlib
endif
ifeq ($(detected_os), Other)
	CFLAGS += -lcryptopp
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
	        src/tools/*.cpp \
		src/tools/packets/*.cpp

FILEIO_SOURCES = src/tools/fileIO/*.cpp \
		src/mainfileIO.cpp


all :
	$(CC) $(CFLAGS) $(WORLD_SOURCES) -L. -lsrc/lib/cryptopp/x64/Output/Release/cryptlib -o master
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
