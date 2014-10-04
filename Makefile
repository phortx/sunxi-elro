CXX=g++

SRCS=send.cpp
DEPS=gpio_lib.o

all: send

send: send.cpp
	$(CXX) -Wall -O3 -o send $(DEPS) $(SRCS)
