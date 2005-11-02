#include "allwind.h"

// Magnitude of a vector:
double Mag(VECTOR &v)
   {
   return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
   }

// Add two vectors
VECTOR Add(VECTOR &v1, VECTOR &v2)
   {
   VECTOR res;

   res.x = v1.x + v2.x;
   res.y = v1.y + v2.y;
   res.z = v1.z + v2.z;

   return res;
   }

// Subtract the two vectors
VECTOR Subtract(VECTOR &v1, VECTOR &v2)
   {
   VECTOR res;

   res.x = v1.x - v2.x;
   res.y = v1.y - v2.y;
   res.z = v1.z - v2.z;

   return res;
   }

// Cross multiply two vectors
VECTOR Cross(VECTOR &v1, VECTOR &v2)
   {
   VECTOR res;

   res.x = v1.y * v2.z - v2.y * v1.z;
   res.y = v1.z * v2.x - v2.z * v1.x;
   res.z = v1.x * v2.y - v2.x * v1.y;

   return res;
   }

// Multiply by constant
VECTOR Multiply(VECTOR &v, double num)
   {
   VECTOR res;

   res.x = v.x * num;
   res.y = v.y * num;
   res.z = v.z * num;

   return res;
   }

// Divide the vector with a scalar
VECTOR Divide(VECTOR &v, double num)
   {
   VECTOR res;

   if ((num > -0.0000000000000000000000001) && (num < 0.0000000000000000000000001))
      {
      num = 0.0000000000000000000000001;
      }

   const double one_over_num = 1 / num;
   res.x = v.x * one_over_num;
   res.y = v.y * one_over_num;
   res.z = v.z * one_over_num;

   return res;
   }

// Normalize the vector
void Normalize(VECTOR &v)
   {
   double len = Mag(v);

   v = Divide(v, len);
   }

// Multiply by constant
double Dot(VECTOR &v, VECTOR &w)
   {
   double res;

   res = v.x * w.x + v.y * w.y + v.z * w.z;

   return res;
   }

// Multiply by constant
VECTOR MVMultiply(MATRIX &s, VECTOR &v)
   {
   VECTOR res;

   res.x = s.e11 * v.x + s.e12 * v.y + s.e13 * v.z;
   res.y = s.e21 * v.x + s.e22 * v.y + s.e23 * v.z;
   res.z = s.e31 * v.x + s.e32 * v.y + s.e33 * v.z;

   return res;
   }

// Multiply by constant
VECTOR MVxyMultiply(MATRIX &s, VECTOR &v)
   {
   VECTOR res;

   res.x = s.e11 * v.x + s.e12 * v.y;
   res.y = s.e21 * v.x + s.e22 * v.y;
   res.z = s.e31 * v.x + s.e32 * v.y;

   return res;
   }

// Multiply by constant
VECTOR MVxMultiply(MATRIX &s, VECTOR &v)
   {
   VECTOR res;

   res.x = s.e11 * v.x;
   res.y = s.e21 * v.x;
   res.z = s.e31 * v.x;

   return res;
   }

// Multiply by constant
VECTOR MVyMultiply(MATRIX &s, VECTOR &v)
   {
   VECTOR res;

   res.x = s.e12 * v.y;
   res.y = s.e22 * v.y;
   res.z = s.e32 * v.y;

   return res;
   }

// Multiply by constant
VECTOR MVy1Multiply(MATRIX &s, VECTOR &  /*v*/)
   {
   VECTOR res;

   res.x = s.e12;
   res.y = s.e22;
   res.z = s.e32;

   return res;
   }

// Multiply by constant
VECTOR MVzMultiply(MATRIX &s, VECTOR &v)
   {
   VECTOR res;

   res.x = s.e13 * v.z;
   res.y = s.e23 * v.z;
   res.z = s.e33 * v.z;

   return res;
   }

// Multiply by constant
MATRIX MMMultiply(MATRIX &m, MATRIX &v)
   {
   MATRIX s;

   s.e11 = m.e11 * v.e11 + m.e12 * v.e21 + m.e13 * v.e31;
   s.e12 = m.e11 * v.e12 + m.e12 * v.e22 + m.e13 * v.e32;
   s.e13 = m.e11 * v.e13 + m.e12 * v.e23 + m.e13 * v.e33;

   s.e21 = m.e21 * v.e11 + m.e22 * v.e21 + m.e23 * v.e31;
   s.e22 = m.e21 * v.e12 + m.e22 * v.e22 + m.e23 * v.e32;
   s.e23 = m.e21 * v.e13 + m.e22 * v.e23 + m.e23 * v.e33;

   s.e31 = m.e31 * v.e11 + m.e32 * v.e21 + m.e33 * v.e31;
   s.e32 = m.e31 * v.e12 + m.e32 * v.e22 + m.e33 * v.e32;
   s.e33 = m.e31 * v.e13 + m.e32 * v.e23 + m.e33 * v.e33;

   return s;
   }

