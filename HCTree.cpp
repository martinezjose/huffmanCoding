#include "HCTree.hpp"

/** Helper method to destruct the tree. It uses recursivity. **/
void clear(HCNode* node) {

  /** Stopping condition **/
  if (node == nullptr) {
    return;
  }

  /** Traverse left **/
  clear(node->c0);

  /** Traverse right **/
  clear(node->c1);

  /** Destroy node **/
  delete node;
}

/** Helper method to traverse from a leave to the root. **/
void traverse(HCNode* node, ofstream& out) {

  if (node == nullptr) {
    return;
  }

  /** Go to the parent **/
  traverse(node->p,out);

  /** If we aren't on the root **/
  if (node->p != nullptr) {

    /** If the node it's the left child of the parent **/
    if (node->p->c0 == node) {
      /*Write 0*/
      out.put('0');
    } else {
      /**Write 1*/
      out.put('1');
    }
  }
}

/** Destructor.  **/
HCTree::~HCTree() {
  clear(root);
  root = nullptr;
}

/** Use the Huffman algorithm to build a Huffman coding trie.
  *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
  *  the frequency of occurrence of byte i in the message.
  *  POSTCONDITION:  root points to the root of the trie,
  *  and leaves[i] points to the leaf node containing byte i.
  */
void HCTree::build(const vector<int>& freqs) {

  /** Create a forest of single-node trees containing symbols and counts for
   *  each non-zero-count symbol **/
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> forest;

  for (uint symbol = 0; symbol < freqs.size(); ++symbol) {
    /** Get count **/
    int count = freqs[symbol];

    /** If count is different than 0, create new node **/
    if (count != 0) {
      HCNode* tree = new HCNode(count, symbol);

      /** Point leaves[symbol] to the leaf node containing byte i **/
      leaves[symbol] = tree;

      /** Add tree to forest **/
      forest.push(tree);
    }
  }

  /** Loop while there is more than 1 tree in the forest **/
  while (forest.size() > 1) {

    /** Remove the two lowest count trees **/
    HCNode* c0 = forest.top();
    forest.pop();
    HCNode* c1 = forest.top();
    forest.pop();

    /** Combine these two trees into a new tree (summing their counts) **/
    HCNode* p = new HCNode(c0->count+c1->count, c0->symbol, c0, c1);

    /** Set parent **/
    c0->p = p;
    c1->p = p;

    /** Insert this new tree in the forest **/
    forest.push(p);
  }

  root = forest.top();
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const {

  traverse(leaves[symbol], out);
}


/** Return the symbol coded in the next sequence of bits (represented as
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const {
  /** Get root **/
  HCNode* node = root;

  /**  If node is null, return stopping condition **/
  if (node == nullptr) {
    return -1;
  }

  /** Loop while we haven't reached a leave **/
  while (node->c0 != nullptr || node->c1 != nullptr) {

    /** Get symbol from file **/
    int symbol = in.get();

    /** If b is -1, return as stopping condition**/
    if (symbol == -1) {
      return symbol;
    }

    /** If we get a 0, go left **/
    if (symbol == 48) {
      node = node->c0;

      /** If we get a 1, go right **/
    } else if (symbol == 49) {
      node = node->c1;
    }
  }
  return node->symbol;
}
