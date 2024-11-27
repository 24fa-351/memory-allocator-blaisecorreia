CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = test_memory_manager

all: $(TARGET)

$(TARGET): memory_manager.o test_memory_manager.o
	$(CC) $(CFLAGS) -o $(TARGET) memory_manager.o test_memory_manager.o

memory_manager.o: memory_manager.c memory_manager.h
	$(CC) $(CFLAGS) -c memory_manager.c

test_memory_manager.o: test_memory_manager.c memory_manager.h
	$(CC) $(CFLAGS) -c test_memory_manager.c

clean:
	rm -f *.o $(TARGET)
