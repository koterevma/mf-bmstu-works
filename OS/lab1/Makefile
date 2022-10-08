CC=clang
CFLAGS=-c -Wall -g
LDFLAGS=-g
SOURCES=main.c customalloc.c list.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab1

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o
