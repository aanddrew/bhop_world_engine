export CXX=g++
export CFLAGS=-std=c++14 -g -Wall -fsplit-stack
export LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS=obj/*.o

%.o: %.cpp
	$(CXX) -c -o obj/$@ $< $(LFLAGS)

bhop_world: main.o
	+$(MAKE) -C engine/graphics
	+$(MAKE) -C engine/math
	+$(MAKE) -C engine/game
	+$(MAKE) -C engine/physics
	+$(MAKE) -C engine/gui
	$(CXX) -o bhop_world $(OBJS) $(LFLAGS)

.PHONY : clean
clean:
	-rm $(OBJS)
