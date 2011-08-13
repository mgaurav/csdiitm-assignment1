/**
 * Author : Bharat Singh, CS08B025 (bharatsingh430@gmail.com)
 *          Gaurav Maheshwari, CS08B005 (gaurav.m.iitm@gmail.com)
 *          Mrinal Kumar, CS08B011 (mrinalkumar08@gmail.com)
 */

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
  int numRowsInCache;
  
  vector<LRUQueue> cache;
  vector<Address> addressLog;

  int numColdMiss;
  int numMisses;
  int numHits;

  bool isColdMiss (Address address);

 public:
  Cache (int associativity, int blockSizeInBytes, int cacheSizeInBytes);
  void updateCache (Address address);

  int getAssociativity () {
    return associativity;
  }

  int getBlockSize () {
    return blockSizeInBytes;
  }

  int getCacheSize () {
    return cacheSizeInBytes;
  }

  int getNumColdMiss () {
    return numColdMiss;
  }
  int getNumMisses () {
    return numMisses;
  }
  int getNumHits () {
    return numHits;
  }
};

#endif
