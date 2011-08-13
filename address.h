/**
 * Author : Bharat Singh, CS08B025 (bharatsingh430@gmail.com)
 *          Gaurav Maheshwari, CS08B005 (gaurav.m.iitm@gmail.com)
 *          Mrinal Kumar, CS08B011 (mrinalkumar08@gmail.com)
 */

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
