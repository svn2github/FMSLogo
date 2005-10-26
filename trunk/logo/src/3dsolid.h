extern const double epsilon;
#define NUM_SHADES 255
#define SHARE

typedef VECTOR Point;

struct VERTEXLIST
   {
   Point Vertex;
   VERTEXLIST *Next;
   VERTEXLIST *Prev;
#ifdef SHARE
   VERTEXLIST *Share;
#endif
#ifdef NOASM
   BOOL Hack;
#endif
   };

struct POLYGON
   {
   VERTEXLIST* Vertices; // The vertices of the polygon
   VECTOR Normal;        // The normal of the POLYGON
   double d;             // The d term of the plane which contains the POLYGON
   Point Centroid;       // Centroid of the POLYGON
   COLORREF ColorNdx;    // Index of POLYGON's color
   };

struct PLIST
   { // Points to the POLYGON list data in TriL
   POLYGON *T;  // Points to a specific polygon in the TriL
   PLIST *Next;	// Next PLIST structure
   };

struct BSPNode
   {
   POLYGON* Poly;
   BSPNode* Inside;
   BSPNode* Outside;
   };

struct RGBCOLOR
   {
   BYTE r, g, b;
   };

//#define MAXPOLYDEPTH 666 // Actual limit 
#define MAXPOLYDEPTH 660

#define HC_ON       0
#define HC_IN       1
#define HC_OUT      2
#define HC_SPANNING 3

// This class supports solid three-dimensional objects
class TThreeDSolid : public TThreeD
   {
public:
      HDC MemDC;
      HDC ScreenDC;

      long iPolyCount;
#ifdef NOASM
      long iSplitPolyCount;
#endif
      VECTOR TraverseTree_s;
      BSPNode* Tree;     // Pointer to the root of the BSP tree

      double Ambient;
      double Diffuse;	 // Contributions of light. 0 <- >- 1.0

      int PolyClass;	    // Local variables to Recursive AddtoBSPTree
#ifdef SHARE
      int ThisPointClass;
      int LastInOutPointClass;
#endif

#if !defined(__WIN32__)
      long iPolyDepth;
      BOOL bDepthExceeded;
#endif

      POLYGON* polyA;
      POLYGON* polyB;

      double sideA;
      double sideB;

      Point pt;
      Point ptA;
      Point ptB;

      VERTEXLIST* VerticesStart;
      VERTEXLIST* Vertices;
      VERTEXLIST* VerticesIn;

#ifdef SHARE
      VERTEXLIST* shareA;
      VERTEXLIST* shareB;
      VERTEXLIST* DeferVerticesOut;
      VERTEXLIST* DeferVerticesIn;
#endif

      BOOL bDefer;

      TThreeDSolid();
      ~TThreeDSolid();
      void View();
      void DisposeTree();
      void DisposePolygon(POLYGON* Poly);
      void AddPoint(VERTEXLIST** v, Point &pt);
      void RemovePoint(VERTEXLIST* v);
      void InsertPoint(VERTEXLIST* v, Point &pt);
      void DisposeVertices(VERTEXLIST* v);
      void DisposeFalseShares(VERTEXLIST* v);
      void CalcPlaneEq(POLYGON *Poly);
      void CalcPolyNormal(POLYGON *Poly);
      void PrecomputeCentroid(POLYGON *Poly);
      void DisposeBSP(BSPNode* tree);
      void AddPolygon(VERTEXLIST* Vertices, COLORREF ColorNdx);
      BSPNode* MakeBSPNode(POLYGON* Poly);
      void AddList(PLIST** tlist, POLYGON* Poly);
      double CalcSign(Point& p, POLYGON* Poly);
      void Intersect(POLYGON* Poly, Point& v1, Point& v2, Point& bc);
      void AddToBSPTree(POLYGON* T, BSPNode** Root);
      BOOL WorldToDisplay(double x, double y, double z, POINT& disp);
      COLORREF ComputeColor(Point& p, VECTOR& normal, COLORREF colorNdx);
      void DisplayPolygon(POLYGON* Poly);
      void TraverseTree(BSPNode* tree);
   };

