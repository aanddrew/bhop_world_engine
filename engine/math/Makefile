DEPS=*.h
%.o: %.cpp $(DEPS)
	$(CXX) -c -o ../../obj/$@ $< $(CFLAGS)

all: Vec3.o Vec2.o Mat3.o
