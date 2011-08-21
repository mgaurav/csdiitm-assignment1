/**
 * Author : Mrinal Kumar, CS08B011 (mrinalkumar08@gmail.com)
 *          Bharat Singh, CS08B025 (bharatsingh430@gmail.com)
 */

#include "cache.h"
#include "address.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <math.h>

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


int min(int a, int b) {
 
  if(a >= b)
    return b;
  else 
    return a;
}

void cacheAwareMatrixMultiplication (Cache& cache, int dataSize, int n, int s) {
  
  int i, j, k, l;
  int x, y, z;

  // generate a matrix of specified size
  int matrix1[n][n];
  Address* copied_address1[n][n];
  int matrix2[n][n];
  Address* copied_address2[n][n];
  int matrix3[n][n];
  Address* copied_address3[n][n];
  int linearAddress = 0;
  
  srand(time(NULL));

  //simulating copying matrices to a different location to take care of the fact that elements in the same tile are assigned contiguous linear address so that they are brought together into the ache.

  for (i=0; i < n/s; i++) {
    for (j = 0; j < n/s; j++) {
      //assign linear address of the (i,j)th block in matrix 1, matrix2 and matrix3
      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address1[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	      cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  matrix1[k][l] = rand() % MAX;
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
	  matrix2[k][l] = rand() % MAX;
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
	  matrix3[k][l] = rand() % MAX;
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
	for (x = i*s; x <= min((i+1)*s-1, n-1); x++) {
	  for (y = j*s; y <= min((j+1)*s-1, n-1); y++) {
	    for (z = k*s; z <= min((k+1)*s-1, n-1); z++) {
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

void cacheAwareMatrixMultiplication1 (Cache& cache, int dataSize, int n, int s) {
  
  int i, j, k, l;
  int x, y, z;

  // generate a matrix of specified size
  int matrix1[n][n];
  Address* copied_address1[n][n];
  int matrix2[n][n];
  Address* copied_address2[n][n];
  int matrix3[n][n];
  Address* copied_address3[n][n];
  int linearAddress = 0;

  // code to fill copied_address1,2,3 according to your scheme
  for (i=0; i < n/s; i++) {
    for (j = 0; j < n/s; j++) {
      //assign linear address of the (i,j)th block in matrix 1, matrix2 and matrix3
      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address1[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	      cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  matrix1[k][l] = rand() % MAX;
	  linearAddress++;
	}
      }

      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address2[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	      cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  matrix2[k][l] = rand() % MAX;
	  linearAddress++;
	}
      }

      for (k = 0; k<s; k++) {
	for (l = 0; l<s; l++) {
	  copied_address3[i*s+k][j*s+l] = getAddress(linearAddress, cache.getAssociativity(),
	      cache.getBlockSize(), cache.getCacheSize(), dataSize);
	  matrix3[k][l] = rand() % MAX;
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
	for (x = i*s; x <= min((i+1)*s-1, n-1); x++) {
	  for (y = j*s; y <= min((j+1)*s-1, n-1); y++) {
	    for (z = k*s; z <= min((k+1)*s-1, n-1); z++) {
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
  
  if (argc != 6) {
    cout << "Usage: ./exe <cache-associativity> <cache-block-size-in-bytes>"
	 << " <cache-size-in-bytes> <data-element-size-in-bytes> <n>\n";
    exit(1);
  }

  int associativity = atoi(argv[1]);
  int blockSizeInBytes = atoi(argv[2]);
  int cacheSizeInBytes = atoi(argv[3]);
  int dataSizeInBytes = atoi(argv[4]);

  int n = atoi(argv[5]); //size of matrix

  int rows_in_cache = cacheSizeInBytes /(blockSizeInBytes*associativity);
  
  Cache cache(associativity, blockSizeInBytes, cacheSizeInBytes);
  Cache fullyAssociativeCache(cacheSizeInBytes/blockSizeInBytes,
				blockSizeInBytes, cacheSizeInBytes);
  
  if (rows_in_cache < 3) {
    // s : matrix partition will be of size s x s
    int s = sqrt(cacheSizeInBytes / (3 * dataSizeInBytes));
    if (s > n)
      s = n;
    cacheAwareMatrixMultiplication(cache, dataSizeInBytes,  n, s);
    cacheAwareMatrixMultiplication(fullyAssociativeCache, dataSizeInBytes,  n, s);
  } else {
    int rows_by_three = rows_in_cache / 3;
    int s = sqrt(rows_by_three * blockSizeInBytes * associativity /dataSizeInBytes);
    int i = s;
    while(n % i != 0) {
      i--;
    }
    s = i;
    cacheAwareMatrixMultiplication1(cache, dataSizeInBytes,  n, s);
    cacheAwareMatrixMultiplication(fullyAssociativeCache, dataSizeInBytes,  n, s);
  }

  int numHits, numMisses, numColdMisses, numCapacityMisses, numConflictMisses;
  numHits = cache.getNumHits();
  numMisses = cache.getNumMisses();
  numColdMisses = cache.getNumColdMiss();
  numCapacityMisses = fullyAssociativeCache.getNumMisses() - numColdMisses;
  numConflictMisses = numMisses - numColdMisses - numCapacityMisses;
  if (numConflictMisses < 0)
    numConflictMisses = 0;

  cout << ((float) numHits) / (numHits + numMisses) << ' '
       << numColdMisses << ' ' << numCapacityMisses << ' ' << numConflictMisses << "\n";
  return 0;
}
