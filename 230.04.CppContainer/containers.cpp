/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 04: Contaiers
 * 3. Assignment Description:
 *      Work with a list and a vector
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


#include "testContainers.h"
#include <string>
#include <list>
using namespace std;

list<string> arrayToList(string a[], int num)
{
   list<string> newList;
   for (auto index = 0; index < num; index++)
   {
      newList.push_back(a[index]);
   }
   return newList;
}

/*****************************
 * ARRAY TO LIST BACKWARDS
 *****************************/
list<string> arrayToListBackwards(string a[], int num)
{
   list<string> newList;
   for (auto index = 0; index < num; index++)
   {
      newList.push_front(a[index]);
   }
   return newList;
}

/*****************************
 * LIST TO VECTOR
 *****************************/
vector<string> listToVector(const list<string> & l)
{
   vector<string> data;
   for (auto item : l)
   {
      data.push_back(item);
   }
   return data;
}

/*****************************
 * LIST TO VECTOR BACKWARDS
 *****************************/
vector<string> listToVectorBackwards(const list<string>& l)
{
   vector<string> data;
   for (auto rit = l.rbegin(); rit != l.rend(); rit++)
   {
      data.push_back(*rit);
   }
   return data;
}

/*****************************
 * FIND ELEMENT IN VECTOR
 *****************************/
bool findElementInVector(const vector<string> & v, const string& element)
{
   return false;
}

/*****************************
 * MAIN
 *****************************/
int main()
{
   TestCollection().run();
   return 0;
}
