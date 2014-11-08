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
    cout << "./compress called with incorrect arguments." << endl;
    cout << "Usage: ./compress infile outfile" << endl;
    return -1;
  }

  /** Check that the two files are not equal **/
  if (strcmp(argv[1], argv[2]) == 0) {
    cout << "infile and outfile must be different files." << endl;
    return -1;
  }

  /** Input and output streams**/
  ifstream inFile;
  ofstream outFile;

  /** Try opening input file **/
  inFile.open(argv[1], std::ifstream::binary);

  /** Check for errors **/
  if (inFile.fail()) {
    cerr << "Error opening input file: " << strerror(errno) << "." << endl;
    return -1;
  }

  /** Try opening output file **/
  outFile.open(argv[2], std::ofstream::binary);

  /** Check for errors **/
  if (outFile.fail()) {
    cerr << "Error opening output file: " << strerror(errno) << "." << endl;
    inFile.close();
    return -1;
  }

  /** Declare BitInputStream and BitOutputStream objects object **/
  BitOutputStream outStream = BitOutputStream(outFile);
  BitInputStream inStream = BitInputStream(inFile);

  /** Create tree **/
  HCTree tree = HCTree();

  /** Create frequencies vector **/
  vector<int> freqs = vector<int>(256, 0);

  /** Create symbol variable **/
  int symbol;

  cout << "Reading from file \"" <<  argv[1] << "\"... ";
  /** Get frequencies **/
  while (1) {
    /** Read character **/
    symbol = inStream.readByte();
    if (inFile.eof()) {
      break;
    }
    /** Increment frequency **/
    freqs[symbol]++;
  }
  cout << "done." << endl;

  /** Build tree **/
  cout << "Building Huffman code tree... ";
  tree.build(freqs);
  cout << "done." << endl;

  /** Write header **/
  cout << "Writing header to file \"" <<  argv[2] << "\"... ";
  int totalSymbols = 0;
  long totalCount = 0;
  for (uint i = 0; i < freqs.size(); i++) {
    /** Increment symbol and freqs count **/
    if (freqs[i] > 0) {
      totalSymbols++;
      totalCount += freqs[i];
    }
    outStream.writeInt(freqs[i]);
  }
  cout << "done." << endl;

  /** Print counts **/
  cout << "Found " << totalSymbols <<
    " unique symbols in the input file of size " << totalCount << " bytes." <<
    endl;

  /** Rewind input file **/
  inFile.clear();
  inFile.seekg(0, ios::beg);
  cout << "Writing to file \"" << argv[2] << "\"... ";
  while (1) {
    /** Read character **/
    symbol = inStream.readByte();
    if (inFile.eof()) {
      break;
    }
    /** Encode character to the output file **/
    tree.encode(symbol, outStream);
  }
  outStream.flush();
  cout << "done." << endl;

  /** Close both file streams **/
  inFile.close();
  outFile.close();
}
