/*************************************************************
 * Name:
 *      Allocation Test
 * Description:
 *      Validate allocation functions:
 *          allocateOneFloat()
 *          deleteOneFloat()
 *          allocateArrayDouble()
 *          deleteArrayDouble()
 * Author:
 *      Br. Helfrich
 **************************************************************/

#pragma once

#include "unitTest.h"
#include "allocate.h"

/**************************************
 * TEST ALLOCATE
 **************************************/
class TestAllocate : public UnitTest
{
public:
   void run()
   {
      reset();

      // one float
      test_allocateOneFloat();
      test_deleteOneFloat();
      
      // array of doubles
      test_allocateArrayDouble_1();
      test_allocateArrayDouble_4();
      test_allocateArrayDouble_0();
      test_allocateArrayDouble_negative();
      test_deleteArrayDouble_1();
      test_deleteArrayDouble_4();
      test_deleteArrayDouble_0();

      report("Allocate");
   }
private:

   /****************************
    * ARRAY DOUBLE
    ****************************/

   // allocate one double
   void test_allocateArrayDouble_1()
   {  // setup
      double * p = (double *)0xbadf00d;
      // exercise
      p = allocateArrayDouble(1);
      // verify
      assertCondition(p != (double *)0xbadf00d);     // the variable should change
      assertCondition(p != nullptr);                 // better be a valid value
      p[0] = 99.99;                                  // we need to be able to write to this memory
      // teardown
      delete [] p;
   }
   
   // allocate four double
   void test_allocateArrayDouble_4()
   {  // setup
      double * p = (double *)0xbadf00d;
      // exercise
      p = allocateArrayDouble(4);
      // verify
      assertCondition(p != (double *)0xbadf00d);     // the variable should change
      assertCondition(p != nullptr);                 // better be a valid value
      p[0] = 99.99;                                  //  we need to be able to write to this memory
      p[1] = 88.88;
      p[2] = 77.77;
      p[3] = 66.66;
      // teardown
      delete [] p;
   }
   
   // allocate nothing
   void test_allocateArrayDouble_0()
   {  // setup
      double * p = (double *)0xbadf00d;
      // exercise
      p = allocateArrayDouble(0);
      // verify
      assertCondition(p == nullptr);
      // teardown
   }
   
   // allocate nothing
   void test_allocateArrayDouble_negative()
   {  // setup
      double * p = (double *)0xbadf00d;
      // exercise
      p = allocateArrayDouble(-10);
      // verify
      assertCondition(p == nullptr);
      // teardown
   }
   
   // delete one double
   void test_deleteArrayDouble_1()
   {  // setup
      double * p = new double[1];
      double * pCopy = p;
      p[0] = 99.99;
      // exercise
      deleteArrayDouble(p);
      // verify
      assertCondition(p == nullptr);            // address should be zero
      assertCondition(*pCopy != 99.99);         // value in memory should be overwritten
      // teardown
   }
   
   // delete four doubles
   void test_deleteArrayDouble_4()
   {  // setup
      double * p = new double[10];
      double * pCopy = p;
      p[0] = 99.99;
      p[1] = 88.88;
      p[2] = 77.77;
      p[3] = 66.66;
      // exercise
      deleteArrayDouble(p);
      // verify
      assertCondition(p == nullptr);            // address should be zero
      assertCondition(pCopy[0] != 99.99);       // value in memory should be overwritten
      // teardown
   }
   
   // delete nothing
   void test_deleteArrayDouble_0()
   {  // setup
      double * p = nullptr;
      // exercise
      deleteArrayDouble(p);
      // verify
      assertCondition(p == nullptr);
      // teardown
   }
   
   /****************************
    * ONE FLOAT
    ****************************/
   
   // allocate one float
   void test_allocateOneFloat()
   {  // setup
      float * p = (float *)0xbadf00d;
      // exercise
      p = allocateOneFloat((float)3.14);
      // verify
      assertCondition(p != (float *)0xbadf00d);      // the variable should change
      assertCondition(p != nullptr);                 // better be a valid value
      assertValues((double)*p, 3.14, 0.001);         // initialize the value
      *p = (float)99.99;                             // we need to be able to write to this memory
      // teardown
      delete p;
   }
   
   // delete one float
   void test_deleteOneFloat()
   {  // setup
      float value = (float)99.9;
      float * p = new float(value);
      float * pCopy = p;
      // exercise
      deleteOneFloat(p);
      // verify
      assertCondition(p == nullptr);              // address should be zero
      assertCondition(*pCopy != (float)99.99);    // value in memory should be overwritten
      // teardown
   }
};
