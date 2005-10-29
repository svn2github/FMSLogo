class VECTOR
   {
public:
   double x, y, z;
   }
;

class MATRIX
   {
public:

   double e11;
   double e12;
   double e13;

   double e21;
   double e22;
   double e23;

   double e31;
   double e32;
   double e33;
   }
;

double Mag(VECTOR &v);
VECTOR Add(VECTOR &v1, VECTOR &v2);
VECTOR Subtract(VECTOR &v1, VECTOR &v2);
VECTOR Cross(VECTOR &v1, VECTOR &v2);
VECTOR Multiply(VECTOR &v, double num);
VECTOR Divide(VECTOR &v, double num);
void Normalize(VECTOR &v);
double Dot(VECTOR &v1, VECTOR &v2);
VECTOR MVMultiply(MATRIX &v, VECTOR &m);
VECTOR MVxyMultiply(MATRIX &v, VECTOR &m);
VECTOR MVxMultiply(MATRIX &v, VECTOR &m);
VECTOR MVyMultiply(MATRIX &v, VECTOR &m);
VECTOR MVy1Multiply(MATRIX &v, VECTOR &m);
VECTOR MVzMultiply(MATRIX &v, VECTOR &m);
MATRIX MMMultiply(MATRIX &v, MATRIX &m);

