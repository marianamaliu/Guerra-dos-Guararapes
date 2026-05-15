CC = gcc
CFLAGS = -Wall -I./raylib/include -I./include
LDFLAGS = -L./raylib/lib
LIBS = -lraylib -lpthread -ldl -lm -lX11

SRC = main.c $(wildcard src/*.c)
TARGET = guararapes.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)