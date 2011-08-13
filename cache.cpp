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
 * Returns true if a Cold Miss has occured, otherwise false.
 */
bool Cache::isColdMiss (Address address) {
  vector<Address>::iterator iterator;
  for (iterator = addressLog.begin(); iterator != addressLog.end(); iterator++) {
    if (iterator->getSet() == address.getSet() &&
	iterator->getIndex() == address.getIndex()) {
      return false;
    }
  }
  return true;
}

/**
 * Updates cache appropriately when an access to 'address' occurs.
 * Updates Hit count, Miss count, Cold Miss count appropriately.
 */
void Cache::updateCache (Address address) {
  if (isColdMiss(address)) {
    numColdMiss++;
    addressLog.push_back(address);
  }

  bool status = cache[address.getSet()].updateLRUQueue(address);
  if (status)
    numHits++;
  else
    numMisses++;
}
