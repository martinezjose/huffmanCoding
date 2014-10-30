#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

using namespace std;

typedef unsigned char byte;

/** A class, instances of which are nodes in an HCTree. **/
class HCNode {
  friend bool comp(HCNode* one, HCNode* other);

public:
  int count;
  /** Byte in the file we're keeping track of. **/
  byte symbol;
  /** Pointer to '0' child. **/
  HCNode* c0;
  /** Pointer to '1' child. **/
  HCNode* c1;
  /** Pointer to parent. **/
  HCNode* p;

  HCNode(int count,
   byte symbol,
   HCNode* c0 = 0,
   HCNode* c1 = 0,
   HCNode* p = 0)
    : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

  /** Less-than comparison, so HCNodes will work in std::priority_queue.
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool operator< (const HCNode& other);
};

/** For printing an HCNode to an ostream.
 *  Possibly useful for debugging.
 */
ostream& operator<< (ostream&, const HCNode&) __attribute__((weak));

/** Shut the linker up. **/
ostream& operator<< (ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}

bool comp(HCNode* one, HCNode* other);

#endif /** HCNODE_HPP **/
