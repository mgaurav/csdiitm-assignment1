#ifndef CACHE_H
#define CACHE_H

#include "address.h"
#include "lruqueue.h"

#include <vector>

using namespace std;

class Cache
{
  int cacheSizeInBytes;
  int associativity;
  int blockSizeInBytes;
  int dataSizeInBytes;
  int numRowsInCache;
  
  LRUQueue* cache;
  vector<Address> addressLog;

  int numColdMiss;
  int numMisses;
  int numHits;

  //int getTagFromLinearAddress (int linearAddress); 
  //CacheLine generateCacheLine (int linearAddress);
  //bool isCacheLineEmpty (CacheLine cacheLine);
  //bool isPresentInCache (int linearAddress);
  bool isColdMiss (Address address);

 public:
  Cache (int associativity, int blockSizeInBytes, int cacheSizeInBytes, int dataSizeInBytes);
  void updateCache (Address address);

  int getNumColdMiss () {
    return numColdMiss;
  }
  int getMisses () {
    return numMisses;
  }
  int getNumHits () {
    return numHits;
  }
};

#endif
