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

## Files
### compress.cpp
The compress.cpp file contains the code needed for the compression. When run, this program reads the contents of the file named by its first command line argument, constructs a Huffman tree for the contents of that file, and uses the Huffman tree to encode the data into binary. The encoded data is essentially the compressed version of the contents of the input file and are written to a output file named by the second command line argument. The binary executable, which will be named compress, can be run as follows:
```./compress infile outfile```
infile is the file to be compressed. outfile will be the compressed version of the file.

### uncompress.cpp
The uncompress.cpp file will contain the code needed for the decompression. When run, this program reads the contents of the file named by its first command line argument. This file should be one that has been created by your compress program. It uses the contents of that file to reconstruct the original, uncompressed version, which is written to a file named by the second command line argument. The binary executable, which will be named uncompress, can be run as follows:
```./uncompress infile outfile```
infile is the file to be decompressed. outfile will be the decompressed version of the file.

### HCNode.hpp / HCNode.cpp
The implementation of the Huffman tree will contain nodes, each holding pointers to the left and right children of that node as well as a pointer to the parent node. What's new in the nodes of the Huffman tree are the members count and symbol, which hold the frequency of a particular symbol and its symbol ID, respectively.
In addition the HCNode class overloads the < operator. To construct the Huffman tree correctly, nodes are placed into a priority queue, and removed according to the priority rule. Since an HCNode is not a primitive type, the priority queue can not determine which node to give higher priority to without some help help. Overriding the < operator is used to help the priority queue compare two nodes and subsequently assign the correct priorities. If two nodes have the same count, there exist a deterministic way of giving one of the nodes higher priority.

### HCTree.hpp / HCTree.cpp
One crucial data structure is a binary tree that represents the Huffman tree and further provides the encoding and decoding functionalities. The HCTree.hpp header file provided to you specifies possible interfaces for this structure. Additionally, the HCTree.cpp file implements the interfaces specified in HCTree.hpp.
Encoding is the process of determining the bit stream for the compression part of the project, and the decoding is used for decompressing the data.

### BitInputStream.hpp / BitInputStream.cpp
The BitInputStream is used for decompression. When reading the compressed file from disk, we start at the root of the tree, then read a single bit at a time while traversing the tree until we reach a leaf node. The leaf will be the original symbol that was encoded from the source file. Since the smallest chunk of data that can be read from a file is a byte (8 bits), a buffer to hold the chunk of data read from the file and implemenent additional functionality to assist with bit level reads is implemented.
The initial contents of the compressed file is a header with the necessary information to decompress your input file. This information is extracted at the four-byte level.

### BitOutputStream.hpp / BitOutputStream.cpp
The BitOutputStream is used for compression. When writing the compressed file to disk, we are going to be encoding bits. We start at the leaf of the tree, and traverse towards the root keeping track of whether to encode a 0 or a 1. However, since we most likely will have a bit string with a length not divisible by eight (the length of a byte), we have to store these bits in a buffer and write them to disk only when the buffer is full.
