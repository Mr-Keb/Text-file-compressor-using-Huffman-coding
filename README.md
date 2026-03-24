# Huffman File Compressor

This project is a lossless file compressor and decompressor implemented in C++23. It utilizes the Huffman coding algorithm to achieve data compression by assigning variable-length binary codes to characters based on their frequency of occurrence .

## Theoretical Limitations (The Brutal Truth)

It is crucial to understand the mathematical limits of this algorithm. This software is an educational tool designed to demonstrate Information Theory concepts. 

- **Best Use Case:** Text files or binary files with high data redundancy (where certain bytes appear much more frequently than others).
- **Worst Use Case:** Pre-compressed files such as `.zip` archives, `.jpg` images, or `.mp4` videos. These formats already possess maximum entropy, meaning the byte distribution is almost flat. If an attempt is made to compress such files, the resulting file will actually be **larger** than the original. The algorithm cannot compress random noise, and the inclusion of the Huffman tree header (necessary for decryption) will add overhead (approximately 1.2 KB) to the final file size.

## If using Visual Studio Code
You can add the `tasks.json` file to your `.vscode` directory and compile

## Project Directory Structure

The build system relies on a strictly defined directory structure managed by a custom `Makefile`. The source files must be organized exactly as follows:

```text
HuffmanCompressor/
│
├── Makefile
├── main.cpp
├── src/
│   ├── HuffmanTree.cpp
│   ├── Encoding.cpp
│   └── Decoding.cpp
│
├── include/
│   ├── HuffmanTree.hpp
│   ├── Encoding.hpp
│   └── Decoding.hpp
│
└── obj/          # Automatically generated during the build process
```

## Prerequisites

To compile and run the project from the terminal without an IDE, the following tools must be installed on the system (Linux, macOS, or Windows via MSYS2/WSL):

    C++ Compiler: g++ with C++23 standard support.

    Make Utility: GNU Make for build automation.

## Compilation Guide

Open a terminal, navigate to the root directory of the project (where the Makefile is located), and execute the following commands.
1. Build the Executable
```Bash

make
```
This command triggers the compiler to:

Create the `obj/` directory if it does not exist.

Compile `main.cpp` and all `.cpp` files inside the `src/` directory into object files (`.o`).

Link everything together to generate the final executable named HuffmanCompressor.

2. Clean Build Artifacts

To wipe the compiled files and start fresh (highly recommended before pushing to a Git repository), run:
```Bash

make clean
```

This safely deletes the obj/ directory and the HuffmanCompressor executable.

## Usage Instructions

After a successful build, launch the program:

- On Linux / macOS / WSL:
```Bash

./HuffmanCompressor
```

- On Windows:
```DOS

HuffmanCompressor.exe
```

An interactive menu will appear with three options:

1. **File compression**: Prompts for the name of the file to compress (e.g., document.txt). The target file must be in the same directory as the executable. The software scans the file, builds the Huffman tree, and generates a new compressed file by appending the .huf extension (e.g., document.txt.huf). The original file is not deleted.

2. **File decompression**: Prompts for the original filename (e.g., document.txt). The program automatically searches for the corresponding .huf file, reads the header to rebuild the tree, and extracts the original data bit by bit in pure binary mode. The output is saved with a modified name (e.g., extracted_document.txt) to prevent accidental overwriting.

3. **Exit program**: Terminates the application and safely frees all dynamically allocated memory.
