/**
 * Author : Bharat Singh, CS08B025 (bharatsingh430@gmail.com)
 */

#include "lruqueue.h"
#include "stdio.h"

LRUQueue::LRUQueue (int ways) {
  this->ways = ways;
}

/**
 * Updates queue of addresses appropriately according to
 * LRU Replacement policy.
 * Return true if a Hit occurs, otherwise returns false.
 */
bool LRUQueue::updateLRUQueue (Address address) {
  if (lruQueue.size() == 0) {
    lruQueue.push_back(address);
    return false;
  }
  list<Address>::iterator iterator;
  for (iterator = lruQueue.begin(); iterator != lruQueue.end();
       iterator++) {
    if (iterator->getSet() == address.getSet() && 
	iterator->getIndex() == address.getIndex()) {
      lruQueue.push_back(address);
      lruQueue.erase(iterator);
      return true;
    }
  }
  if (lruQueue.size() == ways) {
    lruQueue.pop_front();
  }
  lruQueue.push_back(address);
  return false;
}
