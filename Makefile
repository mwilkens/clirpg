CXX= g++
LDFLAGS=ncursesw
DEPS = entites.h player.h
CFLAGS=-g -Wall
SRCS = main.cpp player.cpp entities.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

TARGET = clirpg

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $% $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) -l$(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(TARGET)