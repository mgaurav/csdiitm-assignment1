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


int max(int a, int b) {
 
  if(a >= b)
    return a;
  else 
    return b;
}

/**
 *Recusrsive implementation of cache oblivious matrix multiplication algorithm::-
 *Arguments: A
 */


int cacheObliviousRecursion (Cache& cache, int** M1, int initrow1, int initcol1, int  finrow1, int fincol1, int **M2, int  initrow2, int initcol2, int finrow2, int fincol2, int** M3,int initrow3, int initcol3, int finrow3, int fincol3) {
  int m;
  int n;
  int p;

  m = finrow1-initrow1+1;
  n = fincol1-initcol1+1;
  p = fincol2-initcol2+1;

  //handle the base case of the recursion
  if (m==1 && n==1 && p==1) {
    cache.updateCache(*A1[initrow1][initcol1]);
    cache.updateCache(*A2[initrow2][initcol2]);
    cache.updateCache(*A3[initrow3][initcol3]);
    M3[initrow3][initcol3] += M1[initrow1][initcol1] * M2[initrow2][initcol2];
    return 1;
  }

  if (m >= max(n,p)) {
    //partition A and proceed
    cacheObliviousRecursion (cache, M1, initrow1, initcol1,initrow1 + (m-1)/2 , fincol1, M2, initrow2, initcol2, finrow2, fincol2, M3, initrow3, initcol3, initrow3 + (m-1)/2, fincol3);
    cacheObliviousRecursion (cache, M1, initrow1 + (m-1)/2+1, initcol1,initrow1 + m -1 , fincol1, M2, initrow2, initcol2, finrow2, fincol2, M3, initrow3 + (m-1)/2 + 1, initcol3, initrow3 + m -1, fincol3);
    return 1;
  }

  else if (n >= max(m,p)) {
    //partition both A and B and proceed
    cacheObliviousRecursion (cache, M1, initrow1, initcol1, finrow1, initcol1 + (n-1)/2, M2, initrow2, initcol2, initrow2 + (n-1)/2, fincol2, M3, initrow3, initcol3, finrow3, fincol3);
    cacheObliviousRecursion (cache, M1, initrow1, initcol1 + (n-1)/2 + 1, finrow1, initcol1 + n -1, M2, initrow2 + (n-1)/2 + 1, initcol2, initrow2 + n -1, fincol2, M3, initrow3, initcol3, finrow3, fincol3);
    return 1;
  }

  else if (p >= max(n,m)) {
    //partition B and proceed
    cacheObliviousRecursion (cache, M1, initrow1, initcol1, finrow1, fincol1, M2, initrow2, initcol2, finrow2, initcol2 + (p-1)/2, M3, initrow3, initcol3, finrow3, initcol3 + (p-1)/2);
    cacheObliviousRecursion (cache, M1, initrow1, initcol1, finrow1, fincol1, M2, initrow2, initcol2 + (p-1)/2 + 1, finrow2, initcol2 + p -1, M3, initrow3, initcol3 + (p-1)/2 + 1, finrow3, initcol3 + p-1);
    return 1;
  }

}

void cacheObliviousMatrixMultiplication (Cache& cache, int dataSize, int m, int n, int p) {
  
  int i, j, k;

  // generate a matrix of specified size
  int** matrix1 = (int**)malloc(sizeof(int*)*m);
  Address* address1[m][n];
  int** matrix2 = (int**)malloc(sizeof(int*)*n);
  Address* address2[n][p];
  int** matrix3 = (int**)malloc(sizeof(int*)*m);
  Address* address3[m][p];
  int linearAddress = 0;

  A1 = (Address***)malloc(sizeof(Address**)*m);
  A2 = (Address***)malloc(sizeof(Address**)*n);
  A3 = (Address***)malloc(sizeof(Address**)*m);
  for (i  = 0; i<m; i++){
    A1[i] = (Address **)malloc(sizeof(Address*)*n);
    matrix1[i] = (int *)malloc(sizeof(int)*n);
    A3[i] = (Address **)malloc(sizeof(Address*)*p);
    matrix3[i] = (int *)malloc(sizeof(int)*p);
  }

  for (i = 0; i< n; i++){
    A2[i] = (Address **)malloc(sizeof(Address*)*p);
    matrix2[i] = (int *)malloc(sizeof(int)*p);
  }
  
  srand(time(NULL));
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matrix1[i][j] = rand() % MAX;
      A1[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A1[i,j] = address1[i][j];
      linearAddress++;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      matrix2[i][j] = rand() % MAX;
      A2[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A2[i][j] = address2[i][j];
      linearAddress++;
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
      matrix3[i][j] = 0;
      A3[i][j] = getAddress(linearAddress, cache.getAssociativity(),
	  cache.getBlockSize(), cache.getCacheSize(), dataSize);
      //*A3[i][j] = address3[i][j];
      linearAddress++;
    }
  }

  // perform matrix multiplication using recursive calls to function cacheObliviousRecursion
  cacheObliviousRecursion (cache, matrix1, 0, 0, m-1, n-1, matrix2, 0, 0, n-1, p-1, matrix3,0, 0, m-1, p-1);

    
}
    
  


int main (int argc, char* argv[]) {
  
  if (argc != 8) {
    cout << "Usage: ./exe <cache-associativity> <cache-block-size-in-bytes>"
	 << " <cache-size-in-bytes> <data-element-size-in-bytes> <m> <n> <p>"
	 << "\n";
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
  Cache fullyAssociativeCache(cacheSizeInBytes/blockSizeInBytes,
      blockSizeInBytes, cacheSizeInBytes);
  cacheObliviousMatrixMultiplication(cache, dataSizeInBytes, m, n, p);
  cacheObliviousMatrixMultiplication(fullyAssociativeCache, dataSizeInBytes, m, n, p);

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
