#include <iostream>
#include <fstream>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv) {

  HCTree* tree = new HCTree();

  vector<int> freqs = vector<int>(256, 0);

  ifstream inFile;
  int nextChar;
  inFile.open("input_files/lotsofA");
  while(1){
    nextChar = inFile.get();
    freqs[nextChar]++;
    if(inFile.eof()){
      break;
    }
  }

  tree->build(freqs);
  ifstream.seekg(0, ios::beg);
  ofstream outFile;
  
  outFile.open("test.txt");
  tree->encode()

  inFile.close();
  /** Consider using this way of constructing the leaves vector!!
  if (tree->leaves[byte] == nullptr) {
    tree->leaves[byte] = new HCNode();
  }
  tree->leaves[byte]->count++;
  **/
}
