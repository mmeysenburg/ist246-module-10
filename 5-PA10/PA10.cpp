#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "mpi.h"
#include <random>
#include <vector>

bool isSorted(double *pArr, int n) {
    for(int i = 0; i < n - 1; i++) {
        if(pArr[i] > pArr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* pArgv[]) {

    // OpenMPI variables
    int rank;
    int nProcs;

    // initialize MPI constructs
    MPI_Init(&argc, &pArgv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcs);

    // MPI message identifiers
    int SEND = 0;
    int RECV = 1;

    // array size
    int n = 10000000;

    //-------------------------------------------------------------------------
    // master process section of the code
    //-------------------------------------------------------------------------
    if(rank == 0) {
        // create initial unsorted array
        std::mt19937_64 prng(time(0));
        std::uniform_real_distribution<double> dist;
        double *pArr = new double[n];
        for(int i = 0; i < n; i++) {
            pArr[i] = dist(prng);
        }

        // divide into 5 buckets
        std::vector<std::vector<double>> buckets;
        for(int i = 0; i < 5; i++) {
            buckets.push_back(std::vector<double>());
            buckets.reserve(n / 5 + 100);
        }
        for(int i = 0; i < n; i++) {
            buckets[(int)(pArr[i] * 5)].push_back(pArr[i]);
        }

        // TODO: send to 5 subprocessors.  Use vector data() method
        // to get the array holding values for a bucket
        for(int i = 0; i < 5; i++) {
            std::cout << "sending " << buckets[i].size() << " to " << (i + 1) << std::endl;
        }

        int received;
        int offset = 0;
        MPI_Status status;
        // TODO: receive data from subprocessors
        for(int i = 1; i <= 5; i++) {
            // TODO: recieve data from subprocessor i, placing results in pArr.
            // Use offset to indicate correct starting position for each 
            // successive call.

            // TODO: use MPI_Get_count to determine how many values were 
            // received

            // TODO: update offset so next set of values are placed correctly


            std::cout << "received " << received << " values from " << i << std::endl;
        }

        // validate that the array is really sorted
        if(isSorted(pArr, n)) {
            std::cout << "Array is sorted!" << std::endl;
        } else {
            std::cout << "Array is NOT sorted!" << std::endl;
        }

        // free array memory
        delete [] pArr;
    } else {
        //---------------------------------------------------------------------
        // subprocessor section of the code
        //---------------------------------------------------------------------

        // use MPI_Probe to tell how big my local buffer needs to be
        int subN = 0;
        MPI_Status status;
        MPI_Probe(0, SEND, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI::DOUBLE, &subN);

        // allocate subprocessor memory
        double *pSubArr = new double[subN];

        // TODO: receive values into the subprocessor array


        std::cout << "\t" << rank << " received " << subN << " values." << std::endl;

        // TODO: sort the subprocessor array with std::sort


        // TODO: send subprocessor array back to master process


        // free subprocessor memory
        delete [] pSubArr;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}