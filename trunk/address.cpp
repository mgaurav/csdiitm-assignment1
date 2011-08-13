/**
 * Author : Bharat Singh, CS08B025 (bharatsingh430@gmail.com)
 */

#include "address.h"

Address::Address (int set, int index, int offset) {
  this->set = set;
  this->index = index;
  this->offset = offset;
}

int Address::getSet () {
  return set;
}

int Address::getIndex () {
  return index;
}

int Address::getOffset () {
  return offset;
}
