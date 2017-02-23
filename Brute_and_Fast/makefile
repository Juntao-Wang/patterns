all: Fast Brute
Fast: Fast_main.o Fast.o pointlist.o point.o
	g++ -o Fast Fast_main.o Fast.o pointlist.o point.o
Brute: Brute_main.o Brute.o pointlist.o point.o
	g++ -o Brute Brute_main.o Brute.o pointlist.o point.o
Fast_main.o: Fast_main.cpp Fast.h
	g++ -c Fast_main.cpp
Fast.o: Fast.cpp Fast.h
	g++ -c Fast.cpp
Brute.o: Brute.cpp Brute.h
	g++ -c Brute.cpp
Brute_main.o: Brute_main.cpp Brute.h
	g++ -c Brute_main.cpp
pointlist.o: pointlist.cpp pointList.h
	g++ -c pointlist.cpp
point.o: point.cpp Point.h
	g++ -c point.cpp
clean:
	rm *.o