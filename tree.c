#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

int addChar(char letter, Tree* charList, int length) {
  for (int i = 0; i < length; i++) {
    if (charList[i]->val == letter) {
      charList[i]->freq++;
      return length;
    }
  }
  
  Tree temp = malloc(sizeof(Node));
  temp->left = NULL;
  temp->right = NULL;
  temp->val = letter;
  temp->freq = 1;
  charList[length] = temp;
  return length + 1;
}

void swap(Tree* charList, int ind1, int ind2) {
  Tree temp = charList[ind1];
  charList[ind1] = charList[ind2];
  charList[ind2] = temp;
}

void bubbleSortList(Tree* charList, int length) {
  for (int i = 0; i < length; i++) {
    int lowest = charList[i]->freq;
    int lowest_index = i;
    for (int j = i + 1; j < length; j++) {
      if (charList[j]->freq < lowest) {
        lowest = charList[j]->freq;
        lowest_index = j;
      }
    }
    swap(charList, i, lowest_index);
  }
}

Tree buildTree(Tree* charList, int length) {
  if (length == 1) {
    return charList[0];
  }
  Tree parent = malloc(sizeof(Node));
  parent->left = charList[0];
  parent->right = charList[1];
  parent->freq = charList[0]->freq + charList[1]->freq;
  int swapSize = 2;
  int pFreq = parent->freq;
  for (int i = 2; i < length; i++) {
    if (swapSize == 2) {
      if (pFreq <= charList[i]->freq) {
        charList[i-2] = parent;
        swapSize = 1;
      }
      swap(charList, i, i - swapSize);
    } else {
      swap(charList, i, i - 1);
    }
  }
  if (swapSize == 2) {
    charList[length-2] = parent;
  }
  return buildTree(charList, length-1);
}

void buildLookup(Tree t, Bit** lookup, int counter) {
  if (t->left == NULL) {
    lookup[t->val] = convertToBits(counter);
    return;
  }
  buildLookup(t->left, lookup, counter * 2);
  buildLookup(t->right, lookup, counter * 2 + 1);
}

Bit* convertToBits(int i) {
  Bit* new;
  Bit* head = malloc(sizeof(Bit));
  head->next = NULL;
  if (i % 2 == 0) {
    head->val = false;
  } else {
    head->val = true;
  }
  i /= 2;
  while(i != 1) {
    new = malloc(sizeof(Bit));
    new->next = head;
    if (i % 2 == 0) {
      new->val = false;
    } else {
      new->val = true;
    }
    i /= 2;
    head = new;
  }
  return head;
}

