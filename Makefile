CC = gcc
CFLAGS = -Wall -Wextra -std=c23
SRC = $(wildcard src/*.c)
TARGET = shell

release: CFLAGS += -O2 -DNDEBUG
release: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

valgrind: $(TARGET)
	valgrind --suppressions=valgrind.supp ./$(TARGET)

clean:
	rm -f $(TARGET)
