# Boots - File Compressor & Decompressor

## Run-Length Encoding (RLE)

Encodes consecutive repeated characters as a single character and count. (for example AAAAA -> 5A)

## Huffman Coding

Compresses data by assigning shorter bit codes to more frequent characters using a binary tree.

## Features

- Compress and decompress files using RLE or Huffman
- CLI-based usage with custom file output
- Built entirely in C

## Installation

Clone the repository and compile the program:

```sh
git clone https://github.com/veronin1/boots.git
cd boots
make
```

## Usage

**Flags:**

- `-c` -> Compress
- `-d` -> Decompress
- `-rle` -> Use Run-Length Encoding
- `-huff` -> Use Huffman Coding

```sh
./boots (-c|-d) (-rle|-huff) <input_file> <output_file>


# Compress a file using Run-Length Encoding (RLE)
./boots -c -rle input_file output.rle

# Compress a file using Huffman Coding
./boots -c -huff input_file output.huff

# Decompress an RLE-compressed file
./boots -d input.rle output_file

# Decompress a Huffman-compressed file
./boots -d input.huff output_file
```

## TODO (Future Idea)

- [ ] Create `-auto` flag to automatically decide which compression algorithm to use based on file content or type
- [ ] Implement file extension check to determine which decompression algorithm to apply
- [ ] Use more complex file compression techniques

## What I Learned

- Fundamentals of data compression
- Data structures like trees, queues, and arrays
- Implementation of **Run-Length Encoding (RLE)** in C
- Implementation of **Huffman Coding** (tree-based compression)
- Use of **priority queues** for building Huffman Trees
- Bit-level manipulation for compact binary encoding/decoding
- File I/O in C
- Recursive algorithms for tree traversal
- Dynamic memory management using `malloc` and `free`
- Handling edge cases and validating compression accuracy
