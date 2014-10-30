#ifdef BITINPUTSTREAM_HPP

/** TODO
 *  Read the next bit from the bit buffer.
 *  If the bit buffer is currently empty,
 *  fill the bit buffer by reading a char from the istream first.
 *  Return the bit read as the least signficant bit of an int.
 *  Return -1 on EOF.
 *  This must be consistent with BitOutputStream::writeBit(), in terms
 *  of ordering of bits in the stream.
 */
int readBit() {
  return 0;
}

/** TODO
 *  Read a byte from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading bytes.
 */
int readByte() {
  return 0;
}

/** TODO
 *  Read a non-negative int from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading ints.
 */
int readInt() {
  return 0;
}

#endif
