#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include "HCTree.hpp"

using namespace std;

/** Driver for decompressing a file. **/
int main(int argc, char** argv) {

  /** Check that the parameter count is correct **/
  if (argc != 3) {
    cout << "Please provide the input file and output file as parameters."
      << endl;
    return -1;
  }

  /** Check that we can open both files **/
  /** Input and output streams**/
  ifstream inFile;
  ofstream outFile;

  /** Try opening input file **/
  inFile.open(argv[1]);

  /** Check for errors **/
  if (inFile.fail()) {
    cerr << "Error opening input file: " << strerror(errno) << endl;
    return -1;
  }

  /** Try opening output file **/
  outFile.open(argv[2]);

  /** Check for errors **/
  if (outFile.fail()) {
    cerr << "Error opening output file: " << strerror(errno) << endl;
    return -1;
  }

  /** Create tree **/
  HCTree* tree = new HCTree();

  /** Create frequencies vector **/
  vector<int> freqs = vector<int>(256, 0);

  /** Get frequencies **/
  int nextChar;
  while(1){
    nextChar = (char)inFile.get();
    freqs[nextChar]++;
    if(inFile.eof()){
      break;
    }
  }

  /** Write header **/
  for (uint i = 0; i < freqs.size(); i++) {
    outFile << freqs[i] << endl;
  }

  /** Build tree **/
  tree->build(freqs);

  /** Rewind input file **/
  inFile.clear();
  inFile.seekg(0, ios::beg);
  while (1) {
    int n = inFile.get();
    cout << (char) n << endl;
    /** Encode every character to the output file **/
    tree->encode(n, outFile);
    if (inFile.eof()) {
      break;
    }
  }

  /** Close both file streams **/
  inFile.close();
  outFile.close();

}
