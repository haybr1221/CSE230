/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/
/**************************************
 * COUNT - ARRAY
 **************************************/
#include <cstring>
using namespace std;

int countArray(char string[], char x)
{
   long len = strlen(string);
   int count = 0;
   
   for (int i = 0; i <= len; i++)
   {
      if (string[i] == x)
      {
         count++;
      }
   }
   return count;
}

/**************************************
 * COUNT - POINTER
 **************************************/
int countPointer(char string[], char x)
{
   int count = 0;
   
   for (char *p = string; *p; p++)
   {
      if (*p == x)
      {
         count++;
      }
   }
   return count;
}
