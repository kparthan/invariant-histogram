all: test 

test: test.o Point3D.o
	g++ -o test.o Point3D.o 

test.o: test.cpp
  g++ -c test.cpp

Point3D.o: Point3D.cpp
  g++ -c Point3D.cpp

clean:
  rm ./test *.o
