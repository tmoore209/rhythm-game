export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
PKGS=raylib
CPPFLAGS=-Wall -Wextra -ggdb -pedantic -std=c++17 `pkg-config --static --cflags $(PKGS)`
LIBS=`pkg-config --static --libs $(PKGS)`
SOURCES=$(wildcard src/*.cpp)

rhythm: src/*.cpp
	g++ $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include $(LIBS)
