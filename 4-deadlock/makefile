all: mpi-deadlock1.mpi mpi-deadlock2.mpi

mpi-deadlock1.mpi:	deadlock1.cpp
	mpic++ -std=c++11 -O3 deadlock1.cpp -o mpi-deadlock1.mpi

mpi-deadlock2.mpi:	deadlock2.cpp
	mpic++ -std=c++11 -O3 deadlock2.cpp -o mpi-deadlock2.mpi

clean:
	rm mpi-deadlock1.mpi mpi-deadlock2.mpi
