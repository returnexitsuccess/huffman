int encode(char* filename);
void writeTree(FILE* ftree, Tree t, char* w, int* i);
void writeBit(FILE* ftree, char* w, int* i, int bit);
void writeByte(FILE* ftree, char* w, int* i, char byte);