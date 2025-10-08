CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = proxy
SRC = proxy.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
	rm -rf cache/*

.PHONY: all clean 