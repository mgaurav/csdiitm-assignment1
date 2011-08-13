/**
 * Author : Gaurav Maheshwari, CS08B005 (gaurav.m.iitm@gmail.com)
 */

#include "cache.h"
#include "address.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

#define MAX 100
using namespace std;

Address* getAddress (int linearAddress, int associativity, int blockSize,
    int cacheSize, int dataSize) {
  int numDataElementsInABlock = blockSize / dataSize;
  int numRowsInCache = cacheSize / (blockSize * associativity);

  int set = (linearAddress % (numDataElementsInABlock * numRowsInCache)) /
      numDataElementsInABlock;
  int index = (linearAddress / numDataElementsInABlock) * numDataElementsInABlock;
  int offset = linearAddress - index;

  return new Address(set, index, offset);
}

void matrixMultiplication (Cache& cache, int dataSize, int m, int n, int p) {
  
  int i, j, k;

  // generate a matrix of specified size
  int matrix1[m][n];
  Address* address1[m][n];
  int matrix2[n][p];
  Address* address2[n][p];
  int matrix3[m][p];
  Address* address3[m][p];
  int linearAddress = 0;
  
  srand(time(NULL));
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matrix1[i][j] = rand() % MAX;
      address1[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      linearAddress++;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      matrix2[i][j] = rand() % MAX;
      address2[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      linearAddress++;
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
      address3[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      linearAddress++;
    }
  }

  // perform matrix multiplication using naive algorithm
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < p; k++) {
	cache.updateCache(*address1[i][k]);
	cache.updateCache(*address2[k][j]);
	cache.updateCache(*address3[i][j]);

	matrix3[i][j] += matrix1[i][k] * matrix2[k][j]; 
      }
    }
  }
}

int main (int argc, char* argv[]) {
  
  if (argc != 8) {
    cout << "Usage: ./exe <cache-associativity> <cache-block-size-in-bytes>"
	 << " <cache-size-in-bytes> <data-element-size-in-bytes> <m> <n> <p>\n";
    exit(1);
  }

  int associativity = atoi(argv[1]);
  int blockSizeInBytes = atoi(argv[2]);
  int cacheSizeInBytes = atoi(argv[3]);
  int dataSizeInBytes = atoi(argv[4]);

  int m = atoi(argv[5]);
  int n = atoi(argv[6]);
  int p = atoi(argv[7]);
  
  Cache cache(associativity, blockSizeInBytes, cacheSizeInBytes);
  matrixMultiplication(cache, dataSizeInBytes, m, n, p);

  cout << "Cache Statistics:\n"
       << "Hits        : " << cache.getNumHits() << "\n"
       << "Misses      : " << cache.getNumMisses() << "\n"
       << "Cold Misses : " << cache.getNumColdMiss() << "\n";

  return 0;
}
