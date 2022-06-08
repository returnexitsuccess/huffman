#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include "decode.h"


int decode(char* filename) {
  FILE* fbin;
  char dir[80] = "./compress/";
  strcat(dir, filename);
  strcat(dir, ".bin");
  fbin = fopen(dir, "rb");
  int textbits;
  fread(&textbits, sizeof(int), 1, fbin);
  int i = 0;
  Char w = 0;
  //for (int j = 0; j < 9; j++) {
  fread(&w, sizeof(Char), 1, fbin);
  //printf("%x\n", w);}
  Tree t = readTree(fbin, &w, &i);
  if (w != 0) {
    printf("Read Tree Failed\n");
  }
  
  // Bit* lookupTable[256];
  // buildLookup(t, lookupTable, 1);
  // Bit* b = lookupTable['A'];
  // while(b != NULL) {
  //   if (b->val == false) {
  //     printf("0");
  //   } else {
  //     printf("1");
  //   }
  //   b = b->next;
  // }
  
  FILE* fout;
  strcpy(dir, "./finish/");
  strcat(dir, filename);
  strcat(dir, ".txt");
  fout = fopen(dir, "w");
  fread(&w, sizeof(Char), 1, fbin);
  i = 0;
  Tree currentHead = t;
  int bit;
  for (int j = 0; j < textbits; j++) {
    bit = readBit(fbin, &w, &i);
    if (bit == 0) {
      currentHead = currentHead->left;
    } else {
      currentHead = currentHead->right;
    }
    if (currentHead->left == NULL) {
      putc(currentHead->val, fout);
      currentHead = t;
    }
  }
  if (w != 0) {
    printf("Read Text Failed\n");
  }
  fclose(fbin);
  
  fseek(fout, 0, SEEK_END);
  int size = ftell(fout);
  
  fclose(fout);
  return size;
}

Tree readTree(FILE* fbin, Char* w, int* i) {
  Tree t = malloc(sizeof(Node));
  if (readBit(fbin, w, i) == 1) {
    t->left = NULL;
    t->right = NULL;
    t->val = readByte(fbin, w, i);
    //printf("1\n%c\n", t->val);
    return t;
  }
  t->left = readTree(fbin, w, i);
  t->right = readTree(fbin, w, i);
  return t;
}

int readBit(FILE* fbin, Char* w, int* i) {
  int bit;
  if ((*w) > 127) {
    bit = 1;
  } else {
    bit = 0;
  }
  (*w) = (*w) << 1;
  (*i) += 1;
  if ((*i) % 8 == 0) {
    fread(w, sizeof(Char), 1, fbin);
  }
  return bit;
}

Char readByte(FILE* fbin, Char* w, int* i) {
  Char nextByte;
  Char byte;
  fread(&nextByte, sizeof(Char), 1, fbin);
  int shift = 8 - ((*i) % 8);
  if (shift != 0) {
    byte = (*w) | (nextByte >> shift);
    (*w) = nextByte << (8-shift);
  } else {
    byte = (*w);
    (*w) = nextByte;
  }
  return byte;
}