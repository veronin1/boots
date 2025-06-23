# CS50X Final Project - File Compressor & Decompressor

## Run-Length Encoding (RLE)
Encodes consecutive repeated characters as a single character and count. (for example AAAAA -> 5A)

## Huffman Coding
Compresses data by assigning shorter bit codes to more frequent characters.

## Features
- Compress and decompress files using RLE or Huffman
- CLI-based usage with custom file output
- Built entirely in C

## Usage
```bash
./boots -c -rle input_file output.rle       # Compress a file using Run-Length Encoding (RLE)

./boots -c -huff input_file output.huff     # Compress a file using Huffman Coding

./boots -d input.rle output_file            # Decompress an RLE-compressed file

./boots -d input.huff output_file           # Decompress a Huffman-compressed file
```

## TODO (Future Idea)

- [ ] Create `-auto` flag to automatically decide which compression algorithm to use based on file content or type
- [ ] Implement file extension check to determine which decompression algorithm to apply
- [ ] Use more complex file compression techniques
