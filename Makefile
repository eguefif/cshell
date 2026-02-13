CC = gcc
CFLAGS = -Wall -Wextra -std=c23
SRC = $(wildcard src/*.c)
TARGET = shell

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
