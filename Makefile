CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -arch arm64
TARGET = task_manager

all: $(TARGET)

$(TARGET): task_manager.c task_manager.h
	$(CC) $(CFLAGS) task_manager.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
