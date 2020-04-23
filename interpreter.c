// SPDX-License-Identifier: CC0-1.0
// Cyclic Brainfuck
// by hiromi-mi, same as public domain. See https://creativecommons.org/publicdomain/zero/1.0/legalcode.

#include <stdio.h>
#include <errno.h>

int bytes[40000];

// by P: '[' は '?' と '!' の間に含まれないので拡張すべき
// '?' - '!' + 1 = 31 : mod31
// '`' - '!' + 1 = 93 -  33 + 1 = mod61
char shuffle(char c, int index) {
   int var = (c + index - '!') % ('`' - '!' + 1);
   return var + '!';
}

int main(int argc, char** argv) {
   char buffer[65536];
   if (argc <= 1) {
      fprintf(stderr, "Usage: ./interpret filename.bf %d\n", -2%3);
      return 1;
   }
   FILE *fp = NULL;
   if ((fp = fopen(argv[1], "r")) == NULL) {
      perror("File open error:");
      return 1;
   }
   fgets(buffer, 65536, fp);
   fclose(fp);

   int *ptr = bytes;
   long long index = 0;
   int pc = 0;
   char c = '\0';
   int cnt = 0;
   for (index=0;buffer[pc] != '\0';index++) {
      c = shuffle(buffer[pc], index);
      switch(c) {
         case '>':
            ptr++; pc++; break;
         case '<':
            ptr--; pc++; break;
         case '+':
            (*ptr)++; pc++; break;
         case '-':
            (*ptr)--; pc++; break;
         case '.':
            putchar(*ptr); pc++; break;
         case ',':
            *ptr = getchar(); pc++; break;
         case '[':
            if (*ptr != 0) {
               pc++;
               break;
            }
            cnt = 0;
            for (;buffer[pc]!='\0';pc++) {
               c = shuffle(buffer[pc], index);
               // recounted [ (such in case '[' and here
               if (c == '[') {
                  cnt++;
               }
               if (c == ']') {
                  cnt--;
                  if (cnt == 0) {
                     pc++; // Next to ]
                     break;
                  }
               }
            }
            break;
         case ']':
            if (*ptr == 0) {
               pc++;
               break;
            }
            cnt = 0;
            for (;pc>=0;pc--) {
               c = shuffle(buffer[pc], index);
               // recounted [ (such in case ']' and here
               if (c == ']') {
                  cnt++;
               }
               if (c == '[') {
                  cnt--;
                  if (cnt == 0) {
                     pc++; // Next to [
                     break;
                  }
               }
            }
            break;
         default:
            pc++;
            break;
      }
   }
   return 0;
}
