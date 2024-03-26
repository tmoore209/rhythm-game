export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
PKGS=raylib
CPPFLAGS=-ggdb -pedantic -std=c++17 `pkg-config --static --cflags $(PKGS)`
LIBS=`pkg-config --static --libs $(PKGS)`
SOURCES=$(wildcard src/*.cpp)
WARNINGS=-Wall -Wextra
IGNORES=-Wno-parentheses -Wno-narrowing -Wno-write-strings

rhythm: src/*.cpp include/*.hpp
	g++ $(WARNINGS) $(IGNORES) $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include $(LIBS)
