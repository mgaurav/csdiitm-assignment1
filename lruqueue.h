#ifndef LRU_QUEUE_H
#define LRU_QUEUE_H

#include <list>
#include "address.h"

using namespace std;

class LRUQueue
{
  list<Address> lruQueue;
  int ways;
 public:
  LRUQueue (int ways);
  bool updateLRUQueue (Address address);
};

#endif
