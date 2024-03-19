export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
PKGS=raylib
# CFLAGS=-Wall -Wextra -ggdb -pedantic -std=c11 `pkg-config --static --cflags $(PKGS)`
CPPFLAGS=-Wall -Wextra -ggdb -pedantic -std=c++17 `pkg-config --static --cflags $(PKGS)`
LIBS=`pkg-config --static --libs $(PKGS)`
SOURCES=$(wildcard src/*.cpp)

rhythm: src/main.cpp
	# $(CC) $(CFLAGS) -o rhythm src/main.cpp $(LIBS)
	g++ $(CPPFLAGS) -o rhythm $(SOURCES) -I ./include $(LIBS)
