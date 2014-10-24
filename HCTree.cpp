#include "HCTree.hpp"
using namespace std;

  void clear(HCNode* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->c0);
    clear(node->c1);

    /** Destroy node **/
    delete node;
  }

/** Destructor  **/
HCTree::~HCTree() {
  
  clear(root);
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

  for (int symbol = 0; symbol < freqs.size(); ++symbol) {
    int count = freqs[symbol];
    if (count != 0) {
      cout << "Symbol: " << (char)symbol << " added to the forest :)" << endl;
      HCNode* tree = new HCNode(count, symbol);
      /** point leaves[symbol] to the leaf node containing byte i **/
      leaves[symbol] = tree;
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
    HCNode* p = new HCNode(c0->count+c1->count, c0->symbol,
      c0, c1);
    cout << "Symbols " << (char)c0->symbol << " and " << (char)c1->symbol << " are being merged, total count now is " << p->count << " and symbol is " << (char)p->symbol << endl;
    c0->p = p;
    c1->p = p;
    /** Insert this new tree in the forest **/
    forest.push(p);
  }

  root = forest.top();
}

void traverse(HCNode* n, ofstream& out) {

  if (!n) {
    return;
  }

  traverse(n,out);

  if(n->p) {
    
    if(n->p->c0 == n) {
      /*Write 0*/
      out.write("0", sizeof("0"));
    } else {
      /**Write 1*/

      out.write("1", sizeof("1"));
    }
  }
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
}

