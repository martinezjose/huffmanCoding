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
    cout << "./uncompress called with incorrect arguments." << endl;
    cout << "Usage: ./uncompress infile outfile" << endl;
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

  /** Get frequencies **/
  int frequency;
  long frequenciesTotal = 0;
  int uniqueSymbols = 0;
  cout << "Reading header from file \"" << argv[1] << "\"... ";
  for (uint i = 0; i < freqs.size(); i++) {
    frequency = inStream.readInt();
    /** If we are at the end of the file **/
    if (inFile.eof()) {
      cout << "Error reading header in input file: Reached EOF." << endl;
      return -1;
    }
    freqs[i] = frequency;
    if (frequency > 0) {
      /** Accumulate frequencies **/
      frequenciesTotal += frequency;
      uniqueSymbols++;
    }
  }
  cout << "done." << endl;

  /** Print found data information **/
  cout << "Uncompressed file will have " << uniqueSymbols <<
    " unique symbols and size " << frequenciesTotal << " bytes." << endl;

  /** Build tree **/
  cout << "Building Huffman code tree... ";
  tree.build(freqs);
  cout << "done." << endl;

  /** While the total count of symbols is > 0 **/
  cout << "Writing to file \"" << argv[2] << "\"... ";
  while (frequenciesTotal > 0) {
    /** Decode next symbol in file **/
    int symbol = tree.decode(inStream);

    /** If we are at the end of the file or we got the stopping condition **/
    if (symbol == -1) {
      cout << "Error decoding input file: Reached EOF." << endl;
      return -1;
    } else if (inFile.eof()) {
      break;
    }

    /** Write to output **/
    outStream.writeByte(symbol);

    /** Decrement frequencies **/
    frequenciesTotal--;
  }
  cout << "done." << endl;

  /** Close both file streams **/
  inFile.close();
  outFile.close();
}
