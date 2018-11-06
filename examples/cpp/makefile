AR=ar -r
CPP=g++
CFLAGS= -fPIC -std=c++11 -Wall -I../../include


all: prog

%.o: %.cpp
	$(CPP) $(CFLAGS) -o $@ -c $<

prog: libtest.a
	$(CPP) $(CFLAGS) $^ -o $@

libtest.a: main.o FakeObject.o
	ar -r  $@ $^ 

clean: src/main.o src/FakeObject.o 
	$(RM) main.o
	$(RM) FakeObject.o
	$(RM) prog
