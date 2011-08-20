/**
 * Author : Gaurav Maheshwari, CS08B005 (gaurav.m.iitm@gmail.com)
 */

#include "cache.h"
#include "address.h"

Cache::Cache (int associativity, int blockSizeInBytes, int cacheSizeInBytes) {
  this->associativity = associativity;
  this->blockSizeInBytes = blockSizeInBytes;
  this->cacheSizeInBytes = cacheSizeInBytes;

  numRowsInCache = cacheSizeInBytes / (associativity * blockSizeInBytes);
  cache.reserve(sizeof(LRUQueue) * numRowsInCache);
  for (int i = 0; i < numRowsInCache; i++) {
    cache.push_back(LRUQueue(associativity));
  }

  numColdMiss = 0;
  numMisses = 0;
  numHits = 0;
}


/**
 * Updates cache appropriately when an access to 'address' occurs.
 * Updates Hit count, Miss count, Cold Miss count appropriately.
 */
void Cache::updateCache (Address address) {
  if (addressLog.find(make_pair(address.getSet(), address.getIndex()))
      == addressLog.end()) {
    addressLog.insert(make_pair(address.getSet(), address.getIndex()));
    numColdMiss++;
  }

  bool status = cache[address.getSet()].updateLRUQueue(address);
  if (status)
    numHits++;
  else
    numMisses++;
}
