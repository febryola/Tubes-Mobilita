CC=gcc -std=c99
TARGET=main.exe
SRC=$(wildcard src/*.c) \
		$(wildcard src/commands/*.c) \
		$(wildcard src/modules/*/*.c)

.SILENT:all

all:
	$(CC) -o $(TARGET) $(SRC) && echo Build Successs.

clean:
	rm $(TARGET)