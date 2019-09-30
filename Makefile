export CXX=g++
export CFLAGS=-std=c++11 -g -Wall
export LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

OBJS=obj/*.o

%.o: %.cpp
	$(CXX) -c -o obj/$@ $< $(LFLAGS)

bhop_world: main.o
	+$(MAKE) -C engine/graphics
	+$(MAKE) -C engine/math
	$(CXX) -o bhop_world $(OBJS) $(LFLAGS)

.PHONY : clean
clean:
	-rm $(OBJS)
