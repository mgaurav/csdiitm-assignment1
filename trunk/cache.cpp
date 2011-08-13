#include "cache.h"
#include "address.h"

Cache::Cache (int associativity, int blockSizeInBytes, int cacheSizeInBytes, int dataSizeInBytes) {
  this->associativity = associativity;
  this->blockSizeInBytes = blockSizeInBytes;
  this->cacheSizeInBytes = cacheSizeInBytes;
  this->dataSizeInBytes = dataSizeInBytes;

  numRowsInCache = cacheSizeInBytes / (associativity * blockSizeInBytes);
  cache = new LRUQueue[numRowsInCache];

  numColdMiss = 0;
  numMisses = 0;
  numHits = 0;
}

/*int Cache::getTagFromLinearAddress (int linearAddress) {
  int numDataElementsInABlock = blockSizeInBytes / dataSizeInBytes;
  return (linearAddress % (numDataElementsInABlock * numRowsInCache))/numDataElementsInABlock;
  }*/

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

void Cache::updateCache (Address address) {
   // int tag = getTagFromLinearAddress(linearAddress);
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
