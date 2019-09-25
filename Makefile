CXX=g++
CFLAGS=-std=c++11 -g
DEPS = engine/math/Vec2.cpp engine/math/Vec3.cpp engine/math/Mat3.cpp engine/graphics/Camera.cpp

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main.o: main.cpp 
	$(CXX) -c -o $@ $< $(CFLAGS)

bhop_world: main.o engine/math/Vec2.o engine/math/Vec3.o engine/math/Mat3.o engine/graphics/Camera.o
	$(CXX) -o bhop_world main.o engine/math/Vec2.o engine/math/Vec3.o engine/math/Mat3.o engine/graphics/Camera.o

clean:
	find . *.o
