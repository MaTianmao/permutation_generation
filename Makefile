all : out mt

out : new.cpp
	g++ -o out new.cpp -std=c++11

mt : multi-threads.cpp
	g++ -o mt multi-threads.cpp -std=c++11 -fopenmp

clean :
	rm -f out mt




