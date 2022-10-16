CC=clang
CFLAGS=-Wall -g
LDFLAGS=-g
SOURCES=main.c customalloc.c
OBJECTS=main.o customalloc.o
TARGET=lab1

all: $(TARGET)
	
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
