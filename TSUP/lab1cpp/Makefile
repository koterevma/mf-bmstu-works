CXX=clang++
CXXFLAGS=-g -Wall -std=c++20
LDFLAGS=-g
BINARY=lab1
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: ${BINARY}

$(BINARY): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

release: CXXFLAGS += -O2
release: $(BINARY)

.PHONY: clean release all

clean:
	rm $(OBJS)
	rm $(BINARY)
