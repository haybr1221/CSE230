/*************************************************************
 * 1. Name:
 *      Hayley Branchflower & Graham McClure
 * 2. Assignment Name:
 *      Practice 06: Templates
 * 3. Assignment Description:
 *      Find the biggest element in an array, and a stack data structure.
 * 4. What was the hardest part? Be as specific as possible.
 *      Remembering how to implement classes
 * 5. How long did it take for you to complete the assignment?
 *      10 minutes
 **************************************************************/

#pragma once

#include <iostream>

 /***************************************
  * FIND BIGGEST
  **************************************/
template <class T>
T findBiggest(T array[], int numElements)
{
   T biggest = array[0];
   for (int i = 1; i < numElements; i++)
      if (array[i] > biggest)
         biggest = array[i];

   return biggest;
}

class TestStack;

/***************************************
 * STACK
 **************************************/
template <class T>
class Stack
{
   friend TestStack;
public:
   Stack() : numElements(0) {}

   // Add an element to the stack
   void push(const T & value)
   {
      if (numElements < 10)
         data[numElements++] = value;
   }

   // Remove an element from the stack
   void pop()
   {
      if (numElements)
         numElements--;
   }

   // Retrieve the top-most element
   T top()
   {
      if (numElements)
         return data[numElements - 1];
      return 0.0;
   }

private:
   T data[10];
   int numElements;
};
