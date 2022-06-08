typedef unsigned char Char;
int decode(char* filename);
Tree readTree(FILE* fbin, Char* w, int* i);
int readBit(FILE* fbin, Char* w, int* i);
Char readByte(FILE* fbin, Char* w, int* i);