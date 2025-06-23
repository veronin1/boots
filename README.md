#### CS50X Final Project - File Compressor & Decompressor

## Run-Length Encoding (RLE)
Encodes consecutive repeated characters as a single character and count. (for example JJJJJ -> 5J)

## Huffman Coding
Compresses data by assigning shorter bit codes to more frequent characters.


## Features
- Compress and decompress `.txt` files using RLE or Huffman
- CLI-based usage with custom file output
- Built entirely in C

## Usage
```bash
./compress -rle input.txt output.rle        # Compress using Run-Length Encoding
./compress -h input.txt output.huff         # Compress using Huffman Coding
./decompress input.(rle/huff) output.txt # Decompress compressed file
```