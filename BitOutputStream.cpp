#include "BitOutputStream.hpp"

/** DONE
 *  Write the least significant bit of the argument into
 *  the bit buffer, and increment the bit buffer index.
 *  Flush to the ostream first if the bit buffer is full.
 *  This must be consistent with BitInputStream::readBit().
 */
void BitOutputStream::writeBit(int bit) {

  // get the least significant bit (0 or 1)
  buf = bit & 1;

  // If bufi is 8, then buffer is full
  if( bufi == 8 ) {
    flush();
  } 

  // shift lsb to the left 7-bufi places 
  // then you OR the lsb with 1 
  buf |= 1 << (7-bufi);

  // increase index
  bufi++;

}

/** NOT NEEDED RIGHT NOW
 *  Write the least significant byte of the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing bytes.
void BitOutputStream::writeByte(int b) {
}
 */

/** DONE 
 *  Write the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing ints.
 */
void BitOutputStream::writeInt(int i) {

  // a simple write with the passed int
  out.write((char*)&i, sizeof(i)); 

}

/** DONE
 *  If the bit buffer contains any bits, flush the bit buffer to the ostream
 *  clear the bit buffer, and set the bit buffer index to 0.
 *  Also flush the ostream itself.
 */
void BitOutputStream::flush() {
 
    out.put(buf);
    out.flush();
    buf = bufi= 0;

}

