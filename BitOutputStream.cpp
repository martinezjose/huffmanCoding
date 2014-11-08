#include "BitOutputStream.hpp"

/** Helper method that sets the value 1 or 0 of the nth bit from the right of
 *  a byte argument, leaving other bits unchanged, and returns the result. **/
char setBit(char b, int bit, int n) {
  /** Clear bit at position n **/
  b = b & ~(1 << n);
  /** Set nth bit to 0 or 1 **/
  return b | (bit << n);
}

/** Write the least significant bit of the argument into
 *  the bit buffer, and increment the bit buffer index.
 *  Flush to the ostream first if the bit buffer is full.
 *  This must be consistent with BitInputStream::readBit().
 */
void BitOutputStream::writeBit(int bit) {
  /** If the buffer index is 8, then the buffer is full; we need to flush it **/
  if (bufi == 8) {
    flush();
  }
  /** Write the least significant bit of bit into the buffer at the current
   *  index **/
  buf = setBit(buf, bit, bufi);
  bufi++;
}

/** Write the least significant byte of the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing bytes.
 */
void BitOutputStream::writeByte(int b) {
  out.put(b);
}

/** Write the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing ints.
 */
void BitOutputStream::writeInt(int i) {
  out.write((char*)& i, sizeof(i));
}

/** If the bit buffer contains any bits, flush the bit buffer to the ostream,
 *  clear the bit buffer, and set the bit buffer index to 0.
 *  Also flush the ostream itself.
 */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = bufi = 0;
}
