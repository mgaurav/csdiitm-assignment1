#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "lruqueue.h"

typedef vector<Address> randomAddresses;

#define MAX 1000
#define INDEX_SIZE 64
#define ASSOC 1


randomAddresses arr;

void generateAddresses() {
  srand (time(NULL));
  int i = 0;
  for (i = 0; i < MAX; i++) {
    int set = 0;
    int index = i;
    int offset = 0;
    Address addr (set, index, offset);
    arr.push_back (addr);
  }
}

int main()
{
  LRUQueue q (ASSOC);
  int i = 0;
  generateAddresses();
  for (i = 0; i < MAX; i++) {
    if (q.updateLRUQueue(arr[i])) {
      printf("Hit\n");
    } else {
      printf("Miss\n");
    }
  }
  return 0;
}
