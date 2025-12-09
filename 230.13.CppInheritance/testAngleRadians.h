/*************************************************************
 * Module
 *      TEST ANGLE
 * Description:
 *      Unit tests for the Angle class 
 **************************************************************/

#pragma once

#include "angle.h"
#include "unitTest.h"
#include <sstream>

#define PI         3.141592653589793238462643383279502
#define ONE_DEGREE (PI / 180.0)

#ifndef TWO_PI
#define TWO_PI 6.28318530718
#endif // TWO_PI

 /************************************
  * TEST ANGLE
  ************************************/
class TestAngle : public UnitTest
{
public:
   void run()
   {
      reset();

      // increment operator
      test_increment_prefixTypical();
      test_increment_prefixMember();
      test_increment_prefixWrap();
      test_increment_postfixTypical();
      test_increment_postfixWrap();
      test_decrement_prefixTypical();
      test_decrement_prefixMember();
      test_decrement_prefixWrap();
      test_decrement_postfixTypical();
      test_decrement_postfixWrap();

      // negative
      test_negative_typical();
      test_negative_wrap();

      // compare
      test_equal_same();
      test_equal_different();
      test_notEqual_same();
      test_notEqual_different();

      // input/output
      test_display_0();
      test_display_90();
      test_display_180();
      test_display_359();
      test_insertion_zero();
      test_insertion_180();
      test_insertion_1();
      test_insertion_point1();
      test_extraction_zero();
      test_extraction_180();
      test_extraction_1();
      test_extraction_point1();
      test_extraction_oneWrap();
      test_extraction_fiveWrap();
      test_extraction_negativeWrap();
      test_extraction_error();

      // constructors
      test_construct_default();
      test_construct_copy0();
      test_construct_copy180();
      test_construct_nondefault0();
      test_construct_nondefault180();
      test_construct_nondefaultWrap();
      test_construct_nondefaultWrapNegative();

      // get
      test_getRadians_0();
      test_getRadians_90();
      test_getRadians_180();
      test_getDegrees_0();
      test_getDegrees_90();
      test_getDegrees_180();

      // normalize
      test_normalize_0();
      test_normalize_typical();
      test_normalize_negative();
      test_normalize_positiveLap();
      test_normalize_positiveManyLaps();
      test_normalize_negativeLap();
      test_normalize_negativeManyLaps();

      // convert
      test_convertToDegrees_0();
      test_convertToDegrees_90();
      test_convertToDegrees_180();
      test_convertToDegrees_negative();
      test_convertToDegrees_negativeFourLaps();
      test_convertToDegrees_fourLaps();
      test_convertToRadians_0();
      test_convertToRadians_90();
      test_convertToRadians_180();
      test_convertToRadians_negative();
      test_convertToRadians_negativeFourLaps();
      test_convertToRadians_fourLaps();

      // set
      test_setRadians_0();
      test_setRadians_90();
      test_setRadians_180();
      test_setRadians_positiveLap();
      test_setRadians_negativeLap();
      test_setDegrees_0();
      test_setDegrees_90();
      test_setDegrees_180();
      test_setDegrees_positiveLap();
      test_setDegrees_negativeLap();

      // display

      report("Angle");
   }
private:

   /***************************************
    * INCREMENT
    ***************************************/

    // increment prefix in the middle : 180 -> 181
   void test_increment_prefixTypical()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = ++a;
      // verify
      assertValues(a.radians, PI + ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI + ONE_DEGREE, 0.0001);
   }  // teardown

   // increment prefix  - ensure it is a member variable
   void test_increment_prefixMember()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a.operator++();
      // verify
      assertValues(a.radians, PI + ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI + ONE_DEGREE, 0.0001);
   }  // teardown

   // increment prefix wrap : 359.5 -> 0.5
   void test_increment_prefixWrap()
   {  // setup
      Angle a;
      a.radians = TWO_PI - ONE_DEGREE / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = ++a;
      // verify
      assertValues(a.radians, ONE_DEGREE / 2.0, 0.0001);
      assertValues(aReturn.radians, ONE_DEGREE / 2.0, 0.0001);
   }  // teardown

   // increment postfix in the middle : 180 -> 181
   void test_increment_postfixTypical()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a++;
      // verify
      assertValues(a.radians, PI + ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI, 0.0001);
   }  // teardown

   // increment postfix wrap : 359.5 -> 0.5
   void test_increment_postfixWrap()
   {  // setup
      Angle a;
      a.radians = TWO_PI - ONE_DEGREE / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a++;
      // verify
      assertValues(a.radians, ONE_DEGREE / 2.0, 0.0001);
      assertValues(aReturn.radians, TWO_PI - ONE_DEGREE / 2.0, 0.0001);
   }  // teardown

   // decrement prefix in the middle : 180 -> 179
   void test_decrement_prefixTypical()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = --a;
      // verify
      assertValues(a.radians, PI - ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI - ONE_DEGREE, 0.0001);
   }  // teardown

   // decrement prefix Membver
   void test_decrement_prefixMember()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a.operator--();
      // verify
      assertValues(a.radians, PI - ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI - ONE_DEGREE, 0.0001);
   }  // teardown

   // decrement prefix wrap : 0.5 -> 365.5
   void test_decrement_prefixWrap()
   {  // setup
      Angle a;
      a.radians = ONE_DEGREE / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = --a;
      // verify
      assertValues(a.radians, TWO_PI - ONE_DEGREE / 2.0, 0.0001);
      assertValues(aReturn.radians, TWO_PI - ONE_DEGREE / 2.0, 0.0001);
   }  // teardown

   // decrement postfix in the middle : 180 -> 179
   void test_decrement_postfixTypical()
   {  // setup
      Angle a;
      a.radians = PI;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a--;
      // verify
      assertValues(a.radians, PI - ONE_DEGREE, 0.0001);
      assertValues(aReturn.radians, PI, 0.0001);
   }  // teardown

   // decrement postfix wrap : 0.5 -> 359.5
   void test_decrement_postfixWrap()
   {  // setup
      Angle a;
      a.radians = ONE_DEGREE / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = a--;
      // verify
      assertValues(a.radians, TWO_PI - ONE_DEGREE / 2.0, 0.0001);
      assertValues(aReturn.radians, ONE_DEGREE / 2.0, 0.0001);
   }  // teardown

   /***************************************
    * NEGATIVE
    ***************************************/

    // negative no wrap   90 -> 270
   void test_negative_typical()
   {  // setup
      Angle a;
      a.radians = PI / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = -a;
      // verify
      assertCondition(a.radians == PI / 2.0);
      assertValues(aReturn.radians, PI + PI / 2.0, 0.0001);
   }  // teardown

   // negative wrap   270 -> 90
   void test_negative_wrap()
   {  // setup
      Angle a;
      a.radians = PI + PI / 2.0;
      Angle aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = -a;
      // verify
      assertCondition(a.radians == PI + PI / 2.0);
      assertValues(aReturn.radians, PI / 2.0, 0.0001);
   }  // teardown

   /***************************************
    * COMPARE
    ***************************************/

    // equivalent same   1.2345 == 1.2345
   void test_equal_same()
   {  // setup
      Angle aLHS;
      aLHS.radians = 1.2345;
      Angle aRHS;
      aRHS.radians = 1.2345;
      bool retValue = false;
      // exercise
      retValue = (aLHS == aRHS);
      // verify
      assertCondition(retValue == true);
      assertCondition(aLHS.radians == 1.2345);
      assertCondition(aRHS.radians == 1.2345);
   }  // teardown

   // equivalent same   1.2345 == 1.2349
   void test_equal_different()
   {  // setup
      Angle aLHS;
      aLHS.radians = 1.2345;
      Angle aRHS;
      aRHS.radians = 1.2349;
      bool retValue = true;
      // exercise
      retValue = (aLHS == aRHS);
      // verify
      assertCondition(retValue == false);
      assertCondition(aLHS.radians == 1.2345);
      assertCondition(aRHS.radians == 1.2349);
   }  // teardown

   // equivalent same   1.2345 != 1.2345
   void test_notEqual_same()
   {  // setup
      Angle aLHS;
      aLHS.radians = 1.2345;
      Angle aRHS;
      aRHS.radians = 1.2345;
      bool retValue = true;
      // exercise
      retValue = (aLHS != aRHS);
      // verify
      assertCondition(retValue == false);
      assertCondition(aLHS.radians == 1.2345);
      assertCondition(aRHS.radians == 1.2345);
   }  // teardown

   // equivalent same   1.2345 != 1.2349
   void test_notEqual_different()
   {  // setup
      Angle aLHS;
      aLHS.radians = 1.2345;
      Angle aRHS;
      aRHS.radians = 1.2349;
      bool retValue = false;
      // exercise
      retValue = (aLHS != aRHS);
      // verify
      assertCondition(retValue == true);
      assertCondition(aLHS.radians == 1.2345);
      assertCondition(aRHS.radians == 1.2349);
   }  // teardown

   /***************************************
    * I/O
    ***************************************/

    // display zero
   void test_display_0()
   {  // setup
      Angle a;
      a.radians = 0.0;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      std::ostringstream out;
      // exercise
      aConst.display(out);
      // verify
      assertCondition(out.str() == std::string("0.0"));
      assertValues(aConst.radians, 0.0, 0.001);
   }  // teardown

   // display 90
   void test_display_90()
   {  // setup
      Angle a;
      a.radians = 1.570795;  // PI / 2
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      std::ostringstream out;
      // exercise
      aConst.display(out);
      // verify
      assertCondition(out.str() == std::string("90.0"));
      assertValues(aConst.radians, 1.570795, 0.001);
   }  // teardown

   // display 180
   void test_display_180()
   {  // setup
      Angle a;
      a.radians = 3.14159;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      std::ostringstream out;
      // exercise
      aConst.display(out);
      // verify
      assertCondition(out.str() == std::string("180.0"));
      assertValues(aConst.radians, 3.14159, 0.001);
   }  // teardown

   // display 359.9
   void test_display_359()
   {  // setup
      Angle a;
      a.radians = 6.27445866; // 359.5 / 360 * 2 PI
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      std::ostringstream out;
      // exercise
      aConst.display(out);
      // verify
      assertCondition(out.str() == std::string("359.5"));
      assertValues(aConst.radians, 6.27445866, 0.001);
   }  // teardown  

   // output for 0
   void test_insertion_zero()
   {  // setup
      Angle a;
      a.radians = 0.0;
      std::ostringstream sout;
      // exercise
      sout << a;
      // verify
      assertCondition(sout.str() == std::string("0.0"));
      assertCondition(a.radians == 0.0);
   }  // teardown

   // output for 180
   void test_insertion_180()
   {  // setup
      Angle a;
      a.radians = PI;
      std::ostringstream sout;
      // exercise
      sout << a;
      // verify
      assertCondition(sout.str() == std::string("180.0"));
      assertCondition(a.radians == PI);
   }  // teardown

   // output for 1 degree
   void test_insertion_1()
   {  // setup
      Angle a;
      a.radians = ONE_DEGREE;
      std::ostringstream sout;
      // exercise
      sout << a;
      // verify
      assertCondition(sout.str() == std::string("1.0"));
      assertCondition(a.radians == ONE_DEGREE);
   }  // teardown

   // output for 0.1 degree
   void test_insertion_point1()
   {  // setup
      Angle a;
      a.radians = ONE_DEGREE / 10.0;
      std::ostringstream sout;
      // exercise
      sout << a;
      // verify
      assertCondition(sout.str() == std::string("0.1"));
      assertCondition(a.radians == ONE_DEGREE / 10.0);
   }  // teardown

   // input for 0
   void test_extraction_zero()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("0.0"));
      assertCondition(!sin.fail());
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, 0.0, 0.0001);
      assertCondition(sin.str() == std::string("0.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for 180
   void test_extraction_180()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("180.0"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, PI, 0.0001);
      assertCondition(sin.str() == std::string("180.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for 1 degree
   void test_extraction_1()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("1.0"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, ONE_DEGREE, 0.0001);
      assertCondition(sin.str() == std::string("1.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for 0.1 degree
   void test_extraction_point1()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("0.1"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, ONE_DEGREE / 10.0, 0.0001);
      assertCondition(sin.str() == std::string("0.1"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for one wrap 360+90 --> 90
   void test_extraction_oneWrap()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("450.0"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, PI / 2.0, 0.0001);
      assertCondition(sin.str() == std::string("450.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for five wraps 360*5 + 90 --> 90
   void test_extraction_fiveWrap()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("1890.0"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, PI / 2.0, 0.0001);
      assertCondition(sin.str() == std::string("1890.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for two negative wraps -270 - 360 --> 90
   void test_extraction_negativeWrap()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("-630.0"));
      // exercise
      sin >> a;
      // verify
      assertValues(a.radians, PI / 2.0, 0.0001);
      assertCondition(sin.str() == std::string("-630.0"));
      assertCondition(!sin.fail());
   }  // teardown

   // input for error
   void test_extraction_error()
   {  // setup
      Angle a;
      a.radians = 999.9;
      std::istringstream sin(std::string("xxx"));
      // exercise
      sin >> a;
      // verify
      assertCondition(a.radians == 999.9);
      assertCondition(sin.str() == std::string("xxx"));
      assertCondition(sin.fail());
   }  // teardown

    /***************************************
    * CONSTRUCTORS
    ***************************************/

    // default constructor
   void test_construct_default()
   {  // setup
      // exercise
      Angle a;
      // verify
      assertValues(a.radians, 0.0, 0.001);
   }  // teardown

   // copy constructor with zero
   void test_construct_copy0()
   {  // setup
      Angle aRHS;
      aRHS.radians = 0.0;
      // exercise
      Angle aLHS(aRHS);
      // verify
      assertValues(aLHS.radians, 0.0, 0.001);
      assertValues(aRHS.radians, 0.0, 0.001);
   }  // teardown

   // copy constructor with 180 degrees
   void test_construct_copy180()
   {  // setup
      Angle aRHS;
      aRHS.radians = 3.14159;
      // exercise
      Angle aLHS(aRHS);
      // verify
      assertValues(aLHS.radians, 3.14159, 0.001);
      assertValues(aRHS.radians, 3.14159, 0.001);
   }  // teardown

   // non-default constructor with zero
   void test_construct_nondefault0()
   {  // setup
      double degrees = 0.0;
      // exercise
      Angle a(degrees);
      // verify
      assertValues(a.radians, 0.0, 0.001);
      assertValues(degrees, 0.0, 0.001);
   }  // teardown

   // 180 degrees
   void test_construct_nondefault180()
   {  // setup
      double degrees = 180.0;
      // exercise
      Angle a(degrees);
      // verify
      assertValues(a.radians, 3.14159, 0.001);
      assertValues(degrees, 180.0, 0.001);
   }  // teardown

   // wrap positive twice
   void test_construct_nondefaultWrap()
   {  // setup
      double degrees = 810.0; // 90 + 360 + 360
      // exercise
      Angle a(degrees);
      // verify
      assertValues(a.radians, 3.14159 / 2.0, 0.001);
      assertValues(degrees, 810.0, 0.001);
   }  // teardown

   // wrap negative twice
   void test_construct_nondefaultWrapNegative()
   {  // setup
      double degrees = -810.0; // -720 - 90
      // exercise
      Angle a(degrees);
      // verify
      assertValues(a.radians, 3.14159 / 2.0 + 3.14159, 0.001);
      assertValues(degrees, -810.0, 0.001);
   }  // teardown

/***************************************
 * GET
 ***************************************/

 // get radians zero
   void test_getRadians_0()
   {  // setup
      Angle a;
      a.radians = 0.0;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getRadians();
      // verify
      assertValues(result, 0.0, 0.001);
      assertValues(aConst.radians, 0.0, 0.001);
   }  // teardown

   // get radians 90
   void test_getRadians_90()
   {  // setup
      Angle a;
      a.radians = 1.570795; // PI / 2
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getRadians();
      // verify
      assertValues(result, 1.570795, 0.001);
      assertValues(aConst.radians, 1.570795, 0.001);
   }  // teardown

   // get radians 180
   void test_getRadians_180()
   {  // setup
      Angle a;
      a.radians = 3.14159;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getRadians();
      // verify
      assertValues(result, 3.14159, 0.001);
      assertValues(aConst.radians, 3.14159, 0.001);
   }  // teardown

   // get degrees zero
   void test_getDegrees_0()
   {  // setup
      Angle a;
      a.radians = 0.0;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getDegrees();
      // verify
      assertValues(result, 0.0, 0.001);
      assertValues(aConst.radians, 0.0, 0.001);
   }  // teardown

   // get degrees 90
   void test_getDegrees_90()
   {  // setup
      Angle a;
      a.radians = 1.570795; // PI / 2
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getDegrees();
      // verify
      assertValues(result, 90.0, 0.001);
      assertValues(aConst.radians, 1.570795, 0.001);
   }  // teardown

   // get degrees 180
   void test_getDegrees_180()
   {  // setup
      Angle a;
      a.radians = 3.14159;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.getDegrees();
      // verify
      assertValues(result, 180.0, 0.001);
      assertValues(aConst.radians, 3.14159, 0.001);
   }  // teardown

 /***************************************
  * NORMALIZE
  ***************************************/

  // normalize 0
   void test_normalize_0()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(0.0);
      // verify
      assertValues(result, 0.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize typical value
   void test_normalize_typical()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(1.23);
      // verify
      assertValues(result, 1.23, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize negative
   void test_normalize_negative()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(-1.0);
      // verify
      assertValues(result, 6.28318530717 - 1.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize one lap in the positive direction
   void test_normalize_positiveLap()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(6.28318530717 + 1.234);
      // verify
      assertValues(result, 1.234, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize ten laps in the positive direction
   void test_normalize_positiveManyLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(6.28318530717 * 10.0 + 2.121);
      // verify
      assertValues(result, 2.121, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize one lap in the negative direction
   void test_normalize_negativeLap()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(-2.0 * 6.28318530717 + 1.234);
      // verify
      assertValues(result, 1.234, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // normalize ten laps in the positive direction
   void test_normalize_negativeManyLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.normalize(-11.0 * 6.28318530717 + 2.121);
      // verify
      assertValues(result, 2.121, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

/***************************************
 * CONVERT
 ***************************************/

 // convert 0 radians to degrees
   void test_convertToDegrees_0()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(0.0);
      // verify
      assertValues(result, 0.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert PI/2 radians to degrees
   void test_convertToDegrees_90()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(1.570795);  // PI / 2
      // verify
      assertValues(result, 90.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert PI radians to degrees
   void test_convertToDegrees_180()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(3.14159);  // PI
      // verify
      assertValues(result, 180.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert -3PI/2 radians to degrees
   void test_convertToDegrees_negative()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(-4.7123889);  // -3PI/2
      // verify
      assertValues(result, 90.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert -10PI + PI/2 radians to degrees
   void test_convertToDegrees_negativeFourLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(-10 * 3.1415926 + 3.1415926 / 2.0);  // -3PI/2
      // verify
      assertValues(result, 90.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert 10PI - PI/2 radians to degrees
   void test_convertToDegrees_fourLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToDegrees(10 * 3.1415926 - 3.1415926 / 2.0);  // -3PI/2
      // verify
      assertValues(result, 270.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert 0 degrees to radians
   void test_convertToRadians_0()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(0.0);
      // verify
      assertValues(result, 0.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert 90 degrees to radians
   void test_convertToRadians_90()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(90.0);
      // verify
      assertValues(result, 1.570795, 0.001);  // PI / 2
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert 180 degrees to radians
   void test_convertToRadians_180()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(180.0);
      // verify
      assertValues(result, 3.14159, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert -90.0 degrees to radians
   void test_convertToRadians_negative()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(-90.0);
      // verify
      assertValues(result, 4.7123889, 0.001);  // 3PI/2
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert four laps + 90 degrees to radians
   void test_convertToRadians_negativeFourLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(-1350.0);  // -4.0 * 360.0 + 90.0
      // verify
      assertValues(result, 3.1415926 / 2.0, 0.001);
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown

   // convert 10PI - PI/2 radians to degrees
   void test_convertToRadians_fourLaps()
   {  // setup
      Angle a;
      a.radians = 99.9;
      const Angle aConst(a);
      assert(aConst.radians == a.radians);
      double result;
      // exercise
      result = aConst.convertToRadians(1710.0);  // 5 *  360 - 90
      // verify
      assertValues(result, 4.7123889, 0.001);  // 3 PI / 2
      assertValues(aConst.radians, 99.9, 0.001);
   }  // teardown


/***************************************
 * SET
 ***************************************/

 // set radians zero
   void test_setRadians_0()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setRadians(0.0);
      // verify
      assertValues(a.radians, 0.0, 0.001);
   }  // teardown

   // set radians 90
   void test_setRadians_90()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setRadians(1.570795);  // PI / 2
      // verify
      assertValues(a.radians, 1.570795, 0.001);
   }  // teardown

   // set radians 180
   void test_setRadians_180()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setRadians(3.14159);
      // verify
      assertValues(a.radians, 3.14159, 0.001);
   }  // teardown

   // set radians 90 + 720 
   void test_setRadians_positiveLap()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setRadians(2.0 * 6.28318530717 + 1.234);
      // verify
      assertValues(a.radians, 1.234, 0.001);
   }  // teardown

   // set radians -720 + 90
   void test_setRadians_negativeLap()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setRadians(-2.0 * 6.28318530717 + 1.234);
      // verify
      assertValues(a.radians, 1.234, 0.001);
   }  // teardown

   // set degrees zero
   void test_setDegrees_0()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setDegrees(0.0);
      // verify
      assertValues(a.radians, 0.0, 0.001);
   }  // teardown

   // set degrees 90
   void test_setDegrees_90()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setDegrees(90.0);
      // verify
      assertValues(a.radians, 1.570795, 0.001);   // PI / 2
   }  // teardown

   // set degrees 180
   void test_setDegrees_180()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setDegrees(180.0);
      // verify
      assertValues(a.radians, 3.14159, 0.001);
   }  // teardown

   // set radians 90 + 720 
   void test_setDegrees_positiveLap()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setDegrees(720.0 + 90.0);
      // verify
      assertValues(a.radians, 1.570795, 0.001);  // PI / 2
   }  // teardown

   // set radians -720 + 90
   void test_setDegrees_negativeLap()
   {  // setup
      Angle a;
      a.radians = 99.99;
      // exercise
      a.setDegrees(-720.0 + 90.0);
      // verify
      assertValues(a.radians, 1.570795, 0.001);  // PI / 2
   }  // teardown
};


/************************************
 * TEST ANGLE RADIAN
 ***********************************/
class TestAngleRadian : public UnitTest
{
public:
   void run()
   {
      reset();

      // Increment
      test_increment_prefixTypical();
      test_increment_prefixWrap();
      test_increment_prefixVirtual();
      test_decrement_prefixTypical();
      test_decrement_prefixWrap();
      test_decrement_prefixVirtual();

      // Display
      test_display_0();
      test_display_180();
      test_display_45();
      test_display_virtual();

      report("Angle Radians");
   }
private:
   
   
   /***************************************
    * INCREMENT
    ***************************************/

   // increment prefix in the middle : 180 -> 202.5
   void test_increment_prefixTypical()
   {  // setup
      AngleRadians a;
      a.radians = PI;
      AngleRadians aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = ++a;
      // verify
      assertValues(      a.radians, PI + PI_EIGHT, 0.0001);
      assertValues(aReturn.radians, PI + PI_EIGHT, 0.0001);
   }  // teardown
   
   // increment prefix wrap : 348.75 --> 11.25
   void test_increment_prefixWrap()
   {  // setup
      AngleRadians a;
      a.radians = TWO_PI - PI_EIGHT / 2.0;
      AngleRadians aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = ++a;
      // verify
      assertValues(      a.radians, PI_EIGHT / 2.0, 0.0001);
      assertValues(aReturn.radians, PI_EIGHT / 2.0, 0.0001);
   }  // teardown
   
   // increment virtual - make sure the virtual keyword is set correctly
   void test_increment_prefixVirtual()
   {  // setup
      AngleRadians a;
      a.radians = 0.0;
      Angle * p = &a;
      // exercise
      ++(*p);
      // verify
      assertValues(a.radians, PI_EIGHT, 0.0001);
   }  // teardown

   // decrement prefix in the middle : 180 -> 157.5
   void test_decrement_prefixTypical()
   {  // setup
      AngleRadians a;
      a.radians = PI;
      AngleRadians aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = --a;
      // verify
      assertValues(      a.radians, PI - PI_EIGHT, 0.0001);
      assertValues(aReturn.radians, PI - PI_EIGHT, 0.0001);
   }  // teardown
   
   // decrement prefix wrap : 11.25 -> 348.75
   void test_decrement_prefixWrap()
   {  // setup
      AngleRadians a;
      a.radians = PI_EIGHT / 2.0;
      AngleRadians aReturn;
      aReturn.radians = 999.999;
      // exercise
      aReturn = --a;
      // verify
      assertValues(      a.radians, TWO_PI - PI_EIGHT / 2.0, 0.0001);
      assertValues(aReturn.radians, TWO_PI - PI_EIGHT / 2.0, 0.0001);
   }  // teardown
   
   // decrement virtual - make sure the virtual keyword is set correctly
   void test_decrement_prefixVirtual()
   {  // setup
      AngleRadians a;
      a.radians = 0.0;
      Angle * p = &a;
      // exercise
      --(*p);
      // verify
      assertValues(a.radians, TWO_PI - PI_EIGHT, 0.0001);
   }  // teardown
   

   
   /***************************************
    * DISPLAY
    ***************************************/
   
   // output for 0 degrees
   void test_display_0()
   {  // setup
      AngleRadians a;
      a.radians = 0.0;
      std::ostringstream sout;
      // exercise
      a.display(sout);
      // verify
      assertCondition(sout.str() == std::string("0.00radians"));
      assertCondition(a.radians == 0.0);
   }  // teardown

   // output for 180 degrees
   void test_display_180()
   {  // setup
      AngleRadians a;
      a.radians = PI;
      std::ostringstream sout;
      // exercise
      a.display(sout);
      // verify
      assertCondition(sout.str() == std::string("3.14radians"));
      assertCondition(a.radians == PI);
   }  // teardown
   
   // output for 45 degrees
   void test_display_45()
   {  // setup
      AngleRadians a;
      a.radians = PI / 4.0;
      std::ostringstream sout;
      // exercise
      a.display(sout);
      // verify
      assertCondition(sout.str() == std::string("0.79radians"));
      assertCondition(a.radians == PI / 4.0);
   }  // teardown
   
   // display virtual - make sure the virtual keyword is set correctly
   void test_display_virtual()
   {  // setup
      AngleRadians a;
      a.radians = 0.0;
      Angle * p = & a;
      std::ostringstream sout;
      // exercise
      p->display(sout);
      // verify
      assertCondition(sout.str() == std::string("0.00radians"));
      assertCondition(a.radians == 0.0);
   }  // teardown

};
