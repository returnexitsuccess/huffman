# huffman

Proof of concept for Huffman coding of text files

Originally written 9/12/2017

## Usage

Compilation
```console
gcc encode.c -c
gcc decode.c -c
gcc tree.c -c
gcc main.c -c
gcc encode.o decode.o tree.o main.o -o main
```

Place any files you want compressed into `start/`.
This program works with ASCII characters only and the file name must end with ".txt".

Then just run the main executable. The program will compress all the text files in `start/` and save the output into a corresponding file in `compress/`. The program will then automatically decompress the compressed file, save the decompressed version in `finish/`, and check that the decompressed version matches the original version.

The program has almost no error reporting so a Segmentation Fault likely means one of your text files contains non-ASCII data.
