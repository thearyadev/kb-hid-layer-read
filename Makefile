CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native -flto -Os -s
LDFLAGS = -lhidapi-hidraw

TARGET = kb-readlayer

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LDFLAGS)
clean:
	rm -f $(TARGET) *.o
