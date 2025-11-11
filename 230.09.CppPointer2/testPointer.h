/*************************************************************
 * Module
 *      TEST POINTER
 * Description:
 *      Unit tests for the Pointer class 
 **************************************************************/

#pragma once

#include "pointer.h"
#include "unitTest.h"


/************************************
 * TEST POINTER
 ************************************/
class TestPointer : public UnitTest
{
public:
   void run()
   {

      // countArray
      reset();
      test_countArray_empty();
      test_countArray_notFound();
      test_countArray_one();
      test_countArray_many();
      test_countArray_all();
      report("countArray()");

      // countPointer
      reset();
      test_countPointer_empty();
      test_countPointer_notFound();
      test_countPointer_one();
      test_countPointer_many();
      test_countPointer_all();
      report("countPointer()");

   }
private:
   
   /***************************************
    * COUNT ARRAY
    ***************************************/

    // count array empty
   void test_countArray_empty()
   {  // setup
      char text[256] = "";
      char letter = 'x';
      int  num = -1;
      // exercise
      num = countArray(text, letter);
      // verify
      assertCondition(num == 0);
      assertCondition(letter == 'x');
      assertCondition(text[0] == '\0');
   }  // teardown

   // count array not found
   void test_countArray_notFound()
   {  // setup
      char text[256] = "abcde";
      char letter = 'x';
      int  num = -1;
      // exercise
      num = countArray(text, letter);
      // verify
      assertCondition(num == 0);
      assertCondition(letter == 'x');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'c');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'e');
      assertCondition(text[5] == '\0');
   }  // teardown

   // count array one instance
   void test_countArray_one()
   {  // setup
      char text[256] = "abcde";
      char letter = 'c';
      int  num = -1;
      // exercise
      num = countArray(text, letter);
      // verify
      assertCondition(num == 1);
      assertCondition(letter == 'c');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'c');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'e');
      assertCondition(text[5] == '\0');
   }  // teardown

   // count array many instances
   void test_countArray_many()
   {  // setup
      char text[256] = "abada";
      char letter = 'a';
      int  num = -1;
      // exercise
      num = countArray(text, letter);
      // verify
      assertCondition(num == 3);
      assertCondition(letter == 'a');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'a');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'a');
      assertCondition(text[5] == '\0');
   }  // teardown

   // count array every letter is found
   void test_countArray_all()
   {  // setup
      char text[256] = "aaaaaaaa";
      char letter = 'a';
      int  num = -1;
      // exercise
      num = countArray(text, letter);
      // verify
      assertCondition(num == 8);
      assertCondition(letter == 'a');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'a');
      assertCondition(text[2] == 'a');
      assertCondition(text[3] == 'a');
      assertCondition(text[4] == 'a');
      assertCondition(text[6] == 'a');
      assertCondition(text[7] == 'a');
      assertCondition(text[8] == '\0');
   }  // teardown

   /***************************************
    * COUNT POINTER
    ***************************************/

    // count pointer empty
   void test_countPointer_empty()
   {  // setup
      char text[256] = "";
      char letter = 'x';
      int  num = -1;
      // exercise
      num = countPointer(text, letter);
      // verify
      assertCondition(num == 0);
      assertCondition(letter == 'x');
      assertCondition(text[0] == '\0');
   }  // teardown

   // count pointer not found
   void test_countPointer_notFound()
   {  // setup
      char text[256] = "abcde";
      char letter = 'x';
      int  num = -1;
      // exercise
      num = countPointer(text, letter);
      // verify
      assertCondition(num == 0);
      assertCondition(letter == 'x');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'c');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'e');
      assertCondition(text[5] == '\0');
   }  // teardown

   // count pointer one instance
   void test_countPointer_one()
   {  // setup
      char text[256] = "abcde";
      char letter = 'c';
      int  num = -1;
      // exercise
      num = countPointer(text, letter);
      // verify
      assertCondition(num == 1);
      assertCondition(letter == 'c');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'c');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'e');
      assertCondition(text[5] == '\0');
   }  // teardown

   // count pointer many instances
   void test_countPointer_many()
   {  // setup
      char text[256] = "abada";
      char letter = 'a';
      int  num = -1;
      // exercise
      num = countPointer(text, letter);
      // verify
      assertCondition(num == 3);
      assertCondition(letter == 'a');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'b');
      assertCondition(text[2] == 'a');
      assertCondition(text[3] == 'd');
      assertCondition(text[4] == 'a');
      assertCondition(text[5] == '\0');
   }  // teardown
   
   // count pointer every letter is found
   void test_countPointer_all()
   {  // setup
      char text[256] = "aaaaaaaa";
      char letter = 'a';
      int  num = -1;
      // exercise
      num = countPointer(text, letter);
      // verify
      assertCondition(num == 8);
      assertCondition(letter == 'a');
      assertCondition(text[0] == 'a');
      assertCondition(text[1] == 'a');
      assertCondition(text[2] == 'a');
      assertCondition(text[3] == 'a');
      assertCondition(text[4] == 'a');
      assertCondition(text[5] == 'a');
      assertCondition(text[6] == 'a');
      assertCondition(text[7] == 'a');
      assertCondition(text[8] == '\0');
   }  // teardown
};
