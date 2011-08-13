#ifndef ADDRESS_H
#define ADDRESS_H

using namespace std;

/**
 * An address looks like 
 * ------------------------
 * |Set  | Index  | Offset|
 * ------------------------
 *
 * Set    -> row in the cache.
 * Index  -> Address of the representative element of the block.
 * Offset -> Offset from the representative element of the block.
 */
class Address
{
  int set;
  int index;
  int offset;

 public:
  Address (int set, int index, int offset);

  int getSet ();
  int getIndex ();
  int getOffset ();
};

#endif
