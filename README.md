# Huffman Encoding

## Overview
Even though disk space and bandwidth are cheaper now than ever before in history, there is also moredata than ever before. So the ability to compress data is still very useful. Compression comes in two flavors, lossless and lossy. It is often possible to make a file significantly smaller without any loss of information whatsoever (lossless compression). One such method, known as Huffman coding, was invented by David Huffman in 1952. 
Huffman code compression is used today as part of JPEG image compression, the MP3 audio compression standards, the Unix file compression command pack, and many other applications. In contrast, many audio and video file formats use a different type of compression known as lossy. With this compression type, some information is lost.

## Style Guidelines
  1. Line width shouldn't be more than 80 characters.
  2. Files should not contain tabs, or trailing whitespace.
  3. The identation should be 2 spaces.
  4. Every code block should be wrapped by braces:
    ```
    if (condition) {
      /** Code here **/
    } else {
      /** More code here **/
    }
    ```

    Notice the spaces between if and the opening parenthesis and the space
    after the closing parenthesis. Also notice the spaces between the word else.

## Programs
### compress.cpp
The compress.cpp file contains the code needed for the compression. When run, this program reads the contents of the file named by its first command line argument, constructs a Huffman tree for the contents of that file, and uses the Huffman tree to encode the data into binary. The encoded data is essentially the compressed version of the contents of the input file and are written to a output file named by the second command line argument. The binary executable, which will be named compress, can be run as follows:
```./compress infile outfile```
infile is the file to be compressed. outfile will be the compressed version of the file.

### uncompress.cpp
The uncompress.cpp file will contain the code needed for the decompression. When run, this program reads the contents of the file named by its first command line argument. This file should be one that has been created by your compress program. It uses the contents of that file to reconstruct the original, uncompressed version, which is written to a file named by the second command line argument. The binary executable, which will be named uncompress, can be run as follows:
```./uncompress infile outfile```
infile is the file to be decompressed. outfile will be the decompressed version of the file.
