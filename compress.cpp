#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include "HCTree.hpp"

using namespace std;

/** Driver for compressing a file. **/
int main(int argc, char** argv) {

  /** Check that the parameter count is correct **/
  if (argc != 3) {
    cout << "Please provide the input file and output file as parameters."
      << endl;
    return -1;
  }

  /** Input and output streams**/
  ifstream inFile;
  ofstream outFile;

  /** Try opening input file **/
  inFile.open(argv[1], std::ifstream::binary);

  /** Check for errors **/
  if (inFile.fail()) {
    cerr << "Error opening input file: " << strerror(errno) << endl;
    return -1;
  }

  /** Try opening output file **/
  outFile.open(argv[2], std::ofstream::binary);

  /** Check for errors **/
  if (outFile.fail()) {
    cerr << "Error opening output file: " << strerror(errno) << endl;
    return -1;
  }

  /** Create tree **/
  HCTree tree = HCTree();

  /** Create frequencies vector **/
  vector<int> freqs = vector<int>(256, 0);

  /** Declare symbol variable **/
  int symbol;

  /** Get frequencies **/
  while (1) {
    /** Read character **/
    int symbol = inFile.get();
    if (inFile.eof()) {
      break;
    }
    /** Increment frequency **/
    freqs[symbol]++;
  }

  /** Write header **/
  for (uint i = 0; i < freqs.size(); i++) {
    outFile << freqs[i] << endl;
  }

  /** Build tree **/
  tree.build(freqs);

  /** Rewind input file **/
  inFile.clear();
  inFile.seekg(0, ios::beg);
  while (1) {
    /** Read character **/
    symbol = inFile.get();
    if (inFile.eof()) {
      break;
    }
    /** Encode character to the output file **/
    tree.encode(symbol, outFile);
  }

  /** Close both file streams **/
  inFile.close();
  outFile.close();
}
