#include "BitInputStream.hpp"

/** Helper method that returns the value 1 or 0 of the nth bit from the right
 *  of a byte argument. **/
char bitVal(char b, int n) {
  /** Right shift b by n bits, bitwise AND the result with 1 **/
  return (b >> n) & 1;
}

/** Read the next bit from the bit buffer.
 *  If the bit buffer is currently empty,
 *  fill the bit buffer by reading a char from the istream first.
 *  Return the bit read as the least signficant bit of an int.
 *  Return -1 on EOF.
 *  This must be consistent with BitOutputStream::writeBit(), in terms
 *  of ordering of bits in the stream.
 */
int BitInputStream::readBit() {
  /** If the buffer index is 8, then the buffer was read; we need to fill it **
   *  with more data **/
  if (bufi == 8) {
    fill();
  }

  if (in.eof()) {
    return -1;
  }

  /** Get the bit at the appropiate location in the bit buffer, and return the
   *  appropiate int **/
  int bit = bitVal(buf, bufi);
  bufi++;
  return bit;
}

/** Read a byte from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading bytes.
 */
int BitInputStream::readByte() {
  int byte = in.get();
  if (in.eof()) {
    return -1;
  }
  return byte;
}

/** Read a non-negative int from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading ints.
 */
int BitInputStream::readInt() {
  int integer;
  in.read((char*) &integer, sizeof(integer));
  if (in.eof()) {
    return -1;
  }
  return integer;
}

/** Fill the buffer from the input. **/
void BitInputStream::fill() {
  buf = in.get();
  bufi = 0;
}
