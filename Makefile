CFLAGS=-std=c++0x -g $(shell pkg-config --cflags liblcb-experimental) 
LDFLAGS=$(shell pkg-config --libs liblcb-experimental) -lboost_program_options

OBJECTS = invariant-histogram.o \
  Polygon.o \
  DistanceHistogram.o \

all: invariant-histogram 

invariant-histogram: $(OBJECTS)
	g++ $(OBJECTS) -o $@ $(LDFLAGS) 

invariant-histogram.o: invariant-histogram.cpp DistanceHistogram.h 
	g++ -c $(CFLAGS) $< -o $@

Polygon.o: Polygon.cpp Polygon.h Header.h
	g++ -c $(CFLAGS) $< -o $@

DistanceHistogram.o: DistanceHistogram.cpp DistanceHistogram.h Header.h
	g++ -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *~ invariant-histogram 

