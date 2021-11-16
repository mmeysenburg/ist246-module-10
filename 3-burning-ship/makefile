all: frac.mpi uni-frac

frac.mpi:	frac.o EasyBMP.o
	mpic++ -std=c++11 -Wall -O3 frac.o EasyBMP.o -o frac.mpi
	
frac.o:	frac.cpp
	mpic++ -std=c++11 -Wall -O3 -c frac.cpp -o frac.o
	
EasyBMP.o:	EasyBMP.cpp
	mpic++ -std=c++11 -Wall -O3 -c EasyBMP.cpp -o EasyBMP.o
	
uni-frac:	uni-frac.o EasyBMP.o
	g++ -std=c++11 -Wall -O3 uni-frac.o EasyBMP.o -o uni-frac
	
uni-frac.o:	uni-frac.cpp
	g++ -std=c++11 -Wall -O3 -c uni-frac.cpp -o uni-frac.o
	
clean:
	*.o frac.mpi uni-frac
