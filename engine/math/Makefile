DEPS=*.h
../../obj/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

all: ../../obj/Vec3.o ../../obj/Vec2.o ../../obj/Mat3.o
