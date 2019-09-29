DEPS=*.h
../../obj/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

all: ../../obj/Camera.o ../../obj/Tri2.o
