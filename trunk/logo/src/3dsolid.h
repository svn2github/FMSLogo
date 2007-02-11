#ifndef _3DSOLID_H_
#define _3DSOLID_H_

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

#define MAXPOLYDEPTH 660 // Actual limit 

#define HC_ON       0
#define HC_IN       1
#define HC_OUT      2
#define HC_SPANNING 3

// This class supports solid three-dimensional objects
class TThreeDSolid : public TThreeD
   {
private:
   HDC m_MemDC;
   HDC m_ScreenDC;


 public: // HACK: should be private
   long m_iPolyCount;
#ifdef NOASM
   long m_iSplitPolyCount;
#endif

   BSPNode* m_Tree;     // Pointer to the root of the BSP tree

   double m_Ambient;
   double m_Diffuse;     // Contributions of light. 0 <- >- 1.0

 private:
   int m_PolyClass;      // Local variables to Recursive AddtoBSPTree
#ifdef SHARE
   int m_ThisPointClass;
   int m_LastInOutPointClass;
#endif

   POLYGON* m_PolyA;
   POLYGON* m_PolyB;

   double m_SideA;
   double m_SideB;

   Point m_PtA;
   Point m_PtB;

   VERTEXLIST* m_VerticesStart;
   VERTEXLIST* m_Vertices;
   VERTEXLIST* m_VerticesIn;

#ifdef SHARE
   VERTEXLIST* m_ShareA;
   VERTEXLIST* m_ShareB;
   VERTEXLIST* m_DeferVerticesOut;
   VERTEXLIST* m_DeferVerticesIn;
#endif

 public:
   TThreeDSolid();
   ~TThreeDSolid();

   void DisposeVertices(VERTEXLIST* v);
   void DisposeTree();
   void View();
   void AddPolygon(VERTEXLIST* Vertices, COLORREF ColorNdx);
   void AddPoint(VERTEXLIST** v, Point &pt);

 private:
   void DisposePolygon(POLYGON* Poly);
   void RemovePoint(VERTEXLIST* v);
   void InsertPoint(VERTEXLIST* v, Point &pt);
   void DisposeFalseShares(VERTEXLIST* v);
   void CalcPlaneEq(POLYGON *Poly);
   void CalcPolyNormal(POLYGON *Poly);
   void PrecomputeCentroid(POLYGON *Poly);
   void DisposeBSP(BSPNode* tree);
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


#endif // _3DSOLID_H_
