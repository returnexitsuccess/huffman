#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include "encode.h"

int encode(char* filename) {
  Tree* charList = malloc(256 * sizeof(Node));
  int length = 0;
  Tree t;
  Bit* lookupTable[256];
  FILE* ftree;
  
  int c;
  FILE *file;
  char dir[80] = "./start/";
  strcat(dir, filename);
  strcat(dir, ".txt");
  file = fopen(dir, "r");
  
  if (file) {
    while ((c = getc(file)) != EOF)
    {
      length = addChar((char)c, charList, length);
    }
  }
  bubbleSortList(charList, length);
  t = buildTree(charList, length);
  buildLookup(t, lookupTable, 1);
  // Bit* b = lookupTable['A'];
  // while(b != NULL) {
  //   if (b->val == false) {
  //     printf("0");
  //   } else {
  //     printf("1");
  //   }
  //   b = b->next;
  // }
  
  strcpy(dir, "./compress/");
  strcat(dir, filename);
  strcat(dir, ".bin");
  ftree = fopen(dir, "wb");
  int i = 0;
  fwrite(&i, sizeof(int), 1, ftree);
  if (ftree) {
    char w = 0;
    writeTree(ftree, t, &w, &i);
    w = w << (8 - (i % 8));
    putc(w, ftree);
  }
  
  rewind(file);
  i = 0;
  if (file) {
    char w = 0;
    Bit* b;
    while ((c = getc(file)) != EOF)
    {
      b = lookupTable[(char)c];
      while (b != NULL) {
        w *= 2;
        if (b->val == true) {
          w++;
        }
        b = b->next;
        i++;
        if (i % 8 == 0) {
          putc(w, ftree);
          w = 0;
        }
      }
    }
    w = w << (8 - (i % 8));
    putc(w, ftree);
    fclose(file);
  }
  
  rewind(ftree);
  fwrite(&i, sizeof(int), 1, ftree);
  
  fseek(ftree, 0, SEEK_END);
  int size = ftell(ftree);
  
  fclose(ftree);
  return size;
}

void writeTree(FILE* ftree, Tree t, char* w, int* i) {
  if (t->left == NULL) {
    writeBit(ftree, w, i, 1);
    writeByte(ftree, w, i, t->val);
    return;
  }
  writeBit(ftree, w, i, 0);
  writeTree(ftree, t->left, w, i);
  writeTree(ftree, t->right, w, i);
}

void writeBit(FILE* ftree, char* w, int* i, int bit) {
  (*w) = ((*w)<<1) + bit;
  (*i)++;
  if ((*i) % 8 == 0) {
    putc((*w), ftree);
    (*w) = 0;
  }
}

void writeByte(FILE* ftree, char* w, int* i, char byte) {
  int shift = 8 - ((*i) % 8);
  putc(((*w)<<shift) | (byte>>(8-shift)), ftree);
  (*w) = (((unsigned char)(-1))>>shift) & byte;
}