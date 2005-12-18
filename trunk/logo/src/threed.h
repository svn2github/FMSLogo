// Threed: Three dimensional viewer.

// Three dimensional viewing class
class TThreeD
   {
 public:
   double A, B, C, D, DVal;
   VECTOR From, At, Up, Light;
   double Angle;
   VECTOR A1, A2, A3;
   long Vl, Vt, Vr, Vb;
   VECTOR Offset;
   double Zmin;
   double Zmax;

   VECTOR Dist;                        // the FROM->AT vector

   TThreeD();
   void WORLDtoPC(double xw, double yw, POINT& pc);
   void SetAt();
   void SetUp();
   void SetClip(double angle, double _Zmin, double _Zmax);
   void SetFrom();
   void SetEye();
   void SetVolume();
   void SetLight();
   BOOL TransformSegment(VECTOR & from3d, VECTOR & to3d, POINT & from2d, POINT & to2d);
   BOOL Clip3DSegment(VECTOR & p1, VECTOR & p2, POINT & from2d, POINT & to2d);
   BOOL TransformPoint(VECTOR & from3d, POINT & from2d);
   BOOL Clip3DPoint(VECTOR & p1, POINT & from2d);

private:
   unsigned int Code(const VECTOR & p) const;
   }
;

