CC=clang
CFLAGS=-Wall
LDFLAGS=-lm
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -DDEBUG
debug: LDFLAGS += -g
debug: all

release: CFLAGS += -O2 -DNDEBUG
release: all

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE) 
