typedef struct Node Node;
struct Node
{
  Node* left;
  Node* right;
  char val;
  int freq;
};
typedef Node * Tree;
typedef struct Bit Bit;
struct Bit
{
  Bit* next;
  bool val;
};
int addChar(char letter, Tree* charList, int length);
void bubbleSortList(Tree* charList, int length);
void swap(Tree* charList, int ind1, int ind2);
Tree buildTree(Tree* charList, int length);
void buildLookup(Tree t, Bit** lookup, int counter);
Bit* convertToBits(int i);
