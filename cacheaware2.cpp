/**
 * Author : Mrinal Kumar, CS08B011 (mrinalkumar08@gmail.com)
 */

#include "cache.h"
#include "address.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

#define MAX 100
using namespace std;
Address*** A1;
Address*** A2;
Address*** A3;

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


int min(int a, int b) {
 
  if(a >= b)
    return b;
  else 
    return a;
}

void blockMultiply(Cache& cache, int** matrix1, int** matrix2, int** matrix3, int i, int j, int k, int s, int p2, int p3, int m, int n, int p) {
  
  int x;
  int y;
  int z;

  for (x = i*s; x < min((i+1)*s-1, m-1); x++) {
    for (y = j*p2; y < min((j+1)*p2-1, p-1); y++) {
      for (z = k*p3; z < min((k+1)*p3-1, n-1); z++) {
	cache.updateCache(*A1[x][z]);
	cache.updateCache(*A2[z][y]);
	cache.updateCache(*A3[x][y]);

	matrix3[x][y] += matrix1[x][z] * matrix2[z][y]; 
      }
    }
  }
  
}

void cacheAwareMatrixMultiplication (Cache& cache, int dataSize, int n, int s) {
  
  int i, j, k, l;
  int x, y, z;

  // generate a matrix of specified size
  int** matrix1 = (int**)malloc(sizeof(int*)*n);
  Address* copied_address1[n][n];
  int** matrix2 = (int**)malloc(sizeof(int*)*n);
  Address* copied_address2[n][n];
  int** matrix3 = (int**)malloc(sizeof(int*)*n);
  Address* copied_address3[n][n];
  int linearAddress = 0;

  A1 = (Address***)malloc(sizeof(Address**)*n);
  A2 = (Address***)malloc(sizeof(Address**)*n);
  A3 = (Address***)malloc(sizeof(Address**)*n);
  for (i  = 0; i<n; i++){
    A1[i] = (Address **)malloc(sizeof(Address*)*n);
    matrix1[i] = (int *)malloc(sizeof(int)*n);
    A3[i] = (Address **)malloc(sizeof(Address*)*n);
    matrix3[i] = (int *)malloc(sizeof(int)*n);
  }

  for (i = 0; i< n; i++){
    A2[i] = (Address **)malloc(sizeof(Address*)*n);
    matrix2[i] = (int *)malloc(sizeof(int)*n);
  }
  
  srand(time(NULL));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      matrix1[i][j] = rand() % MAX;
      A1[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A1[i,j] = address1[i][j];
      linearAddress++;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      matrix2[i][j] = rand() % MAX;
      A2[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A2[i][j] = address2[i][j];
      linearAddress++;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      matrix3[i][j] = 0;
      A3[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A3[i][j] = address3[i][j];
      linearAddress++;
    }
  }

  //simulating copying matrices to a different location to take care of the fact that elements in the same tile are assigned contiguous linear address so that they are brought together into the ache.

  for (i=0; i < n/s; i++) {
    for (j = 0; j < n/s; j++) {
      //assign linear address of the (i,j)th block in matrix 1, matrix2 and matrix3
      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address1[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  linearAddress++;
	}
      }
    }
  }
      
  for (i=0; i < n/s; i++) {
    for (j = 0; j < n/s; j++) {
      //assign linear address of the (i,j)th block in matrix 1, matrix2 and matrix3
      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address2[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  linearAddress++;
	}
      }
    }
  }

  for (i=0; i < n/s; i++) {
    for (j = 0; j < n/s; j++) {
      //assign linear address of the (i,j)th block in matrix 1, matrix2 and matrix3
      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address3[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  linearAddress++;
	}
      }
    }
  }



  // perform matrix multiplication using tile by tile multiplication
  for (i = 0; i < n/s; i++) {
    for (j = 0 ; j < n/s; j++) {
      for (k = 0; k < n/s; k++) {
         //C[i,j] = C[i,j] + A[i,k]*B[k,j]
    	//blockMultiply(cache, matrix1, matrix2, matrix3, i, j, k, s, p2, p3, m, n, p);
	for (x = i*s; x < min((i+1)*s-1, n-1); x++) {
	  for (y = j*s; y < min((j+1)*s-1, n-1); y++) {
	    for (z = k*s; z < min((k+1)*s-1, n-1); z++) {
	      cache.updateCache(*copied_address1[x][z]);
	      cache.updateCache(*copied_address2[z][y]);
	      cache.updateCache(*copied_address3[x][y]);
	      
	      matrix3[x][y] += matrix1[x][z] * matrix2[z][y]; 
	      
	    }
	  }
	}
      }
    }
  }
  
}


int main (int argc, char* argv[]) {
  
  if (argc != 7) {
    cout << "Usage: ./exe <cache-associativity> <cache-block-size-in-bytes>"
	 << " <cache-size-in-bytes> <data-element-size-in-bytes> <n>  <s> \n";
    exit(1);
  }

  int associativity = atoi(argv[1]);
  int blockSizeInBytes = atoi(argv[2]);
  int cacheSizeInBytes = atoi(argv[3]);
  int dataSizeInBytes = atoi(argv[4]);

  int n = atoi(argv[5]);
  int s = atoi(argv[6]);
 
  Cache cache(associativity, blockSizeInBytes, cacheSizeInBytes);
  cacheAwareMatrixMultiplication(cache, dataSizeInBytes,  n, s);

  cout << "Cache Statistics:\n"
       << "Hits        : " << cache.getNumHits() << "\n"
       << "Misses      : " << cache.getNumMisses() << "\n"
       << "Cold Misses : " << cache.getNumColdMiss() << "\n";

  return 0;
}

