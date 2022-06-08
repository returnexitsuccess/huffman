#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include "tree.h"
#include "encode.h"
#include "decode.h"

int compare(char* filename);

//TODO: Check textfile is all ascii before converting

int main() {
  DIR *dir;
  struct dirent *ent;
  int buffersize = 80;
  char file_ext[buffersize];
  char filename[buffersize];
  int len;
  int oldsize;
  int newsize;
  dir = opendir ("./start/");
  printf("\n");
  /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL) {
    memset(file_ext,0,buffersize);
    memset(filename,0,buffersize);
    strcpy(file_ext, ent->d_name);
    if (file_ext[0] != '.') {
      len = strlen(file_ext);
      for (int i = 0; i < len - 4; i++) {
        filename[i] = file_ext[i];
      }
      printf("%s: ", filename);
      newsize = encode(filename);
      oldsize = decode(filename);
      if (compare(filename) == 0) {
        printf("Success\n");
        printf("Original Size: %d Bytes\n", oldsize);
        printf("Compressed Size: %d Bytes\n", newsize);
        printf("Compression Ratio: %d%%\n\n", 100 * newsize / oldsize);
      } else {
        printf("FAILURE\n\n");
      }
    }
  }
  closedir (dir);
  
  // encode("body");
  // decode("body");
  // if (compare("body") == 0) {
  //   printf("success\n");
  // } else {
  //   printf("failure\n");
  // }
  
  return 0;
}

int compare(char* filename) {
  FILE* file1;
  FILE* file2;
  int c1;
  int c2;
  char dir[80];
  
  strcpy(dir, "./start/");
  strcat(dir, filename);
  strcat(dir, ".txt");
  file1 = fopen(dir, "r");
  
  strcpy(dir, "./finish/");
  strcat(dir, filename);
  strcat(dir, ".txt");
  file2 = fopen(dir, "r");
  
  while ((c1 = getc(file1)) != EOF && (c2 = getc(file2)) != EOF)
  {
    if (c1 != c2) {
      fclose(file1);
      fclose(file2);
      return 1;
    }
  }
  fclose(file1);
  fclose(file2);
  return 0;
}
