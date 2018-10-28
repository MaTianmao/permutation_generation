all : out old_out 

out : new.cpp
	g++  -o out new.cpp -std=c++11

old_out : permutation.cpp
	g++ -o old_out permutation.cpp -std=c++11

clean :
	rm -f out old_out *.o




