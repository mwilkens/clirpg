CXX= g++
LDFLAGS=-lX11 -lGL -lpthread -lpng
DEPS = entites.h player.h
CFLAGS=-g -Wall -Wno-trigraphs
SRCS = main.cpp player.cpp entities.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

TARGET = clirpg

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $% $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(TARGET)
