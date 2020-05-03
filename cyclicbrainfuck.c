// SPDX-License-Identifier: CC0-1.0
// 2Cyclic Brainfuck
// by hiromi-mi, same as public domain. See https://creativecommons.org/publicdomain/zero/1.0/legalcode.

#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>

int bytes[40000];

// by P: '[' は '?' と '!' の間に含まれないので拡張すべき
// '?' - '!' + 1 = 31 : mod31
// ']' - '!' + 1 = 93 -  33 + 1 = mod61

char shuffle(char c, int index, int s, char* table) {
   int var = ((int)c + index - '!') % s + '!';
   return table[var];
}

int seed_table(char* table, int len) {
   for (int index=0;index < len;index++) {
      table[index] = index;
   }
   return 0;
}

int init_table(char* table_buffer, char* table) {
   int obj = 0;
   for (int index=0;table_buffer[index] != '\0';index++) {
      if (index % 2 == 0) {
         // read as character
         obj = table_buffer[index];
      } else {
         // write to obj
         table[obj] = table_buffer[index];
      }
   }
   return 0;
}

int main(int argc, char** argv) {
   char buffer[65536];
   char table_buffer[65536];

   int parensis_stack[100];
   int parensis_stack_id = 0;

   if (argc <= 1) {
      fprintf(stderr, "Usage: ./cyclicbrainfuck filename.cyclicbf\n");
      return 1;
   }
   FILE *fp = NULL;
   struct termios tm, tm_save;
   int fd_stdin = fileno(stdin);

   if ((fp = fopen(argv[1], "r")) == NULL) {
      perror("File open error:");
      return 1;
   }
   fgets(buffer, 65536, fp);
   if (feof(fp)) {
      table_buffer[0] = '\0';
   } else {
      fgets(table_buffer, 65536, fp);
   }
   fclose(fp);

   char table[256];
   seed_table(table, 256);
   init_table(table_buffer, table);

   // https://linuxjm.osdn.jp/html/LDP_man-pages/man3/termios.3.html
   // https://web-develop.hatenadiary.org/entry/20071112/1194882731
   // ICANON can be disabled and input per every char
   tcgetattr(fd_stdin, &tm);
   tcgetattr(fd_stdin, &tm_save);
   tm.c_lflag &= ~ICANON;
   tcsetattr(fd_stdin, TCSADRAIN, &tm);

   int *ptr = bytes;
   long long index = 0;
   int pc = 0;
   char c = '\0';
   int cnt = 0;
   int s = 61;

   for (index=0;buffer[pc] != '\0';index++) {
      // Change to New Modular
      if (buffer[pc] < 0) {
         s = -buffer[pc];
         // fprintf(stderr, "New Modular is: %d\n", s);
         index--;
         pc++;
         continue;
      }
      c = shuffle(buffer[pc], index, s, table);
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
            fputc(*ptr, stdout); pc++; break;
         case ',':
            *ptr = getchar();
            pc++; break;
         case '[':
            if (*ptr != 0) {
               parensis_stack[parensis_stack_id++] = pc;
               pc++;
               break;
            }
            cnt = 0;
            for (;buffer[pc]!='\0';pc++) {
               c = shuffle(buffer[pc], index, s, table);
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
               parensis_stack[--parensis_stack_id] = 0;
               pc++;
               break;
            }
            cnt = 0;
            pc = parensis_stack[parensis_stack_id-1] + 1;
            break;
         default:
            pc++;
            break;
      }
   }
   tcsetattr(fd_stdin, TCSADRAIN, &tm_save);
   return 0;
}
