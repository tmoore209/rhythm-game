export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
PKGS=raylib
CFLAGS=-Wall -Wextra -ggdb -pedantic -std=c11 `pkg-config --static --cflags $(PKGS)`
LIBS=`pkg-config --static --libs $(PKGS)`

rhythm: src/main.c
	$(CC) $(CFLAGS) -o rhythm src/main.c $(LIBS)
