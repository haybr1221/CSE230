/*************************************************************
 * 1. Name:
 *      Hayley Branchflower & Graham McClure
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part of the assignement was figuring out the inline functions and handling arrays.
 * 5. How long did it take for you to complete the assignment?
 *      1 hour
 **************************************************************/

 /****************************
  * ALLOCATE ONE FLOAT
  ****************************/

inline float* allocateOneFloat(float newFloat)
{
   float* ptr = new float(newFloat);
   return ptr;
};

/****************************
 * ALLOCATE ARRAY of DOUBLEs
 ****************************/

inline double* allocateArrayDouble(int size)
{
   if (size <= 0)
      return nullptr;
   return new double[size];
};

/****************************
 * DELETE ONE FLOAT
 ****************************/
void deleteOneFloat(float*& ptr)
{
   if (ptr != nullptr)
   {
      delete ptr;
      ptr = nullptr;
   }
};

/****************************
 * DELETE ARRAY of DOUBLEs
 ****************************/

void deleteArrayDouble(double*& ptr)
{
   if (ptr != nullptr)
   {
      delete[] ptr;
      ptr = nullptr;
   }
};
