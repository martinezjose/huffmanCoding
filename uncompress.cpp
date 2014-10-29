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

  /** Get frequencies **/
  int frequency;
  long frequenciesTotal = 0;
  for (uint i = 0; i < freqs.size(); i++) {
    inFile >> frequency;
    freqs[i] = frequency;
    /** Accumulate frequencies **/
    frequenciesTotal += frequency;
  }

  /** Build tree **/
  tree.build(freqs);

  /** While the total count of symbols is > 0 **/
  while (frequenciesTotal > 0) {
    /** Decode next symbol in file **/
    int symbol = tree.decode(inFile);

    /** If we are at the end of the file or we got the stopping condition **/
    if (inFile.eof() || symbol < 0) {
      break;
    }

    /** Write to output **/
    outFile.put(symbol);

    /** Decrement frequencies **/
    frequenciesTotal--;
  }

  /** Close both file streams **/
  inFile.close();
  outFile.close();
}
