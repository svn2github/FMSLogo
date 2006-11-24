// Check user does not do Down,Up, RR, LR
// Check user turns between vertices
// Check number of points


// 3DSOLID.CPP: Displays a solid representation of a three-dimensional
// object. Implements the BSP algorithm described in Chapter 17 in order
// to display the surfaces of objects correctly. Compile with VECTOR.CPP,
// 3DSOLID.RC, and THREED.CPP.
#include "allwind.h"

const double epsilon2=0.001;
// const double epsilon3=0.001;

// Sets up the dimensions of the window and various default values
TThreeDSolid::TThreeDSolid() : TThreeD()
   {
   Ambient = 0.30; Diffuse = 0.60;
   Light.x = -10.0; Light.y = 100; Light.z = 100;
   Light.x = -10.0; Light.y = 100; Light.z = 50;

   Tree = 0;
   iPolyCount = 0;
#ifdef NOASM
   iSplitPolyCount = 0;
#endif
   }

TThreeDSolid::~TThreeDSolid()
   {
   DisposeTree();
   }

void TThreeDSolid::DisposePolygon(POLYGON* Poly)
   {
   DisposeVertices(Poly->Vertices);
   delete Poly;
   }

void TThreeDSolid::DisposeTree()
   {
   DisposeBSP(Tree);
   Tree = 0;
   iPolyCount = 0;
#ifdef NOASM
   iSplitPolyCount = 0;
#endif
   }

// Sets up the dimensions of the window and various default values
void TThreeDSolid::AddPolygon(VERTEXLIST* Vertices, COLORREF ColorNdx)
   {
   POLYGON *t = new POLYGON;
   t->Vertices = Vertices;
   t->ColorNdx = ColorNdx;

   CalcPolyNormal(t);
   CalcPlaneEq(t);
   PrecomputeCentroid(t);

   AddToBSPTree(t, &Tree/*, NULL*/);
   iPolyCount++;
   update_status_vectors();
   }

// Precompute the d term in the plane equation for each polygon.
// The normal of the plane and a point on the plane- -one of
// its vertices--are used to solve for d.
void TThreeDSolid::CalcPlaneEq(POLYGON *Poly)
   {
   Poly->d = -(
      Poly->Normal.x * Poly->Vertices->Vertex.x +
      Poly->Normal.y * Poly->Vertices->Vertex.y +
      Poly->Normal.z * Poly->Vertices->Vertex.z);
   }

// Calculate the normals of the POLYGONs
void TThreeDSolid::CalcPolyNormal(POLYGON *Poly)
   {
   VECTOR dl = Subtract(Poly->Vertices->Vertex, Poly->Vertices->Next->Vertex);
   VECTOR d2 = Subtract(Poly->Vertices->Vertex, Poly->Vertices->Next->Next->Vertex);
   Poly->Normal = Cross(dl, d2);
   Normalize(Poly->Normal);
   }

// precompute the centrolds of all the POLYGONs
void TThreeDSolid::PrecomputeCentroid(POLYGON *Poly)
   {
   VERTEXLIST* vertices = Poly->Vertices;

   Poly->Centroid.x = 0;
   Poly->Centroid.y = 0;
   Poly->Centroid.z = 0;

   double d = 0;

   do
      {
      Poly->Centroid.x += vertices->Vertex.x;
      Poly->Centroid.y += vertices->Vertex.y;
      Poly->Centroid.z += vertices->Vertex.z;
      vertices = vertices->Next;
      d += 1.0;
      } while (vertices != Poly->Vertices);

   Poly->Centroid.x /= d;
   Poly->Centroid.y /= d;
   Poly->Centroid.z /= d;
   }

// Dispose of the BSP tree
void TThreeDSolid::DisposeBSP(BSPNode* tree)
   {
   if (tree)
      {
      DisposeBSP(tree->Outside);
      DisposeBSP(tree->Inside);
      DisposePolygon(tree->Poly);
      delete tree;
      }
   }

// Create a new node for the BSP tree
BSPNode* TThreeDSolid::MakeBSPNode(POLYGON* Poly)
   {
   BSPNode *node = new BSPNode;
   if (!node)
      {
      return NULL;
      }
   node->Poly = Poly;    // Point to the POLYGON's data
   node->Outside = 0;
   node->Inside = 0;
   return node;
   }

// Add the POLYGON to the POLYGON list
void TThreeDSolid::AddList(PLIST** tlist, POLYGON* Poly)
   {
   PLIST *l = *tlist, *nuL, *back = *tlist;
   nuL = new PLIST;
   if (!nuL)
      {
      MessageBox(
         GetActiveWindow(), 
         LOCALIZED_ERROR_OUTOFMEMORY,
         GetApplicationObject()->GetName(), 
         MB_OK | MB_ICONEXCLAMATION);
      return;
      }
   nuL->T = Poly;
   nuL->Next = 0;
   if (l)
      {
      while (l)
         {
         back = l;
         l = l->Next;
         }
      back->Next = nuL;
      }
   else	// List is empty. This is the first node.
      {
      *tlist = nuL;
      }
}

// Calculate the sign that indicates which side of the separation
// plane vertex p is on. Note that a tolerance value is used to account
// for arithmetic round off errors by the computer. This function uses
// the fact that a plane equation is: ax + by + cz + d = 0. If p is
// on the plane and plugged into the equation, the result will be 0.
// If p is not on the plane, the sign of the result indicates which
// side of the plane the point is on.
double TThreeDSolid::CalcSign(Point& p, POLYGON* Poly)
   {
   double value =
      p.x * Poly->Normal.x +
      p.y * Poly->Normal.y +
      p.z * Poly->Normal.z + Poly->d;
//	if (fabs(value) < epsilon2) return 0.0;  // The point is on the plane
/*	else */
   return value;   // The sign of the value indicates which
   }	// side p is on

// Uses a parameteric equation to determine where a line intersects the
// plane. The two vertices v1 and v2 are the endpoints of the line.
void TThreeDSolid::Intersect(
   POLYGON* Poly,
   Point& v1,
   Point& v2,
   Point& loc
)
   {
   double t = -
      (Poly->Normal.x * (       v1.x) + Poly->Normal.y * (       v1.y) + Poly->Normal.z * (       v1.z) + Poly->d) /
      (Poly->Normal.x * (v2.x - v1.x) + Poly->Normal.y * (v2.y - v1.y) + Poly->Normal.z * (v2.z - v1.z));

   loc.x = v1.x + t * (v2.x - v1.x);
   loc.y = v1.y + t * (v2.y - v1.y);
   loc.z = v1.z + t * (v2.z - v1.z);
   }

void TThreeDSolid::AddPoint(VERTEXLIST** v, Point &pt)
   {
   VERTEXLIST * vn = new VERTEXLIST;

   vn->Vertex = pt;
#ifdef SHARE
   vn->Share = NULL;
#endif
#ifdef NOASM
   vn->Hack = 0;
#endif

   if (*v)
      {
      VERTEXLIST* vp = (*v)->Prev;
      (*v)->Prev = vn;
      vp->Next = vn;
      vn->Next = *v;
      vn->Prev = vp;
      }
   else
      {
      *v = vn;
      (*v)->Next = vn;
      (*v)->Prev = vn;
      }
   }

void TThreeDSolid::RemovePoint(VERTEXLIST* v)
   {
   VERTEXLIST * vp = v->Prev;
   VERTEXLIST * vn = v->Next;
//   if (vp == v)
//      {
////      vn = v->Next;
//      printfx("Trouble");
//      return;
//      }
   delete v;
   vp->Next = vn;
   vn->Prev = vp;
   }

/*
void TThreeDSolid::AddPoint(VERTEXLIST** v, Point &pt)
   {
   VERTEXLIST* vn;

   if (*v)
      {
      vn = *v;

      while (vn->Next) vn = vn->Next;
      vn->Next = new VERTEXLIST;
      vn = vn->Next;
      }
   else
      {
      *v = new VERTEXLIST;

      vn = *v;
      }

   vn->Vertex = pt;
   vn->Next = NULL;
#ifdef SHARE
   vn->Share = NULL;
#endif
   vn->Hack = 0;
   }
*/

void TThreeDSolid::InsertPoint(VERTEXLIST* v, Point &pt)
   {
   VERTEXLIST* vn = new VERTEXLIST;

   vn->Vertex = pt;
#ifdef SHARE
   vn->Share = NULL;
#endif

#ifdef NOASM
   vn->Hack = 0;
#endif

   vn->Next = v->Next;
   vn->Prev = v;

   v->Next = vn;
   vn->Next->Prev = vn;
   }

void TThreeDSolid::DisposeVertices(VERTEXLIST* list)
   {
   VERTEXLIST* next;
   VERTEXLIST* curr;

   if (!list) return;

   curr = list;

   do
      {
      next = curr->Next;
      delete curr;
      curr = next;
      } while (curr != list);
   }

void TThreeDSolid::DisposeFalseShares(VERTEXLIST* list)
   {
   VERTEXLIST* curr;

   if (!list) return;
   
	curr = list;

   do 
      {
#ifdef SHARE
      if (curr->Share)
         {
//         char buff[64];
//         sprintf(buff, "ShareX = %ld", (unsigned long) (curr->Share));
//         printfx(buff);
         if (curr->Share->Share == NULL)
            {
//            char buff[64];
//            sprintf(buff, "ShareY = %ld", (unsigned long) (curr->Share));
//            printfx(buff);
            RemovePoint(curr->Share);
            }
         }
#endif
      curr = curr->Next;
      } while (curr != list);
   }

#ifdef NOASM
#define POLYCOUNT 31

VERTEXLIST* Save2 = NULL;
VERTEXLIST* Save3 = NULL;
#endif

// Make the BSP tree structure
void TThreeDSolid::AddToBSPTree(POLYGON* Poly, BSPNode** Root)
   {
   if (!*Root)
      {
#ifdef NOASM
      iSplitPolyCount++;
      update_status_vectors();
      if (iPolyCount == POLYCOUNT)
         {
         iPolyCount = iPolyCount*1;
         }
#endif
      *Root = MakeBSPNode(Poly);
      }
   else
      {
//    VERTEXLIST* VerticesIn;
      VERTEXLIST* VerticesOut;

      VerticesIn = NULL;
      VerticesOut = NULL;

#ifdef SHARE
      DeferVerticesIn = NULL;
      DeferVerticesOut = NULL;

      LastInOutPointClass = HC_ON;
#endif

      PolyClass = HC_ON;           // assume plane_3d and polygon coincident for starters

      Vertices = Poly->Vertices;

      ptA    = Vertices->Vertex;
      sideA  = CalcSign(ptA, (*Root)->Poly);  // classify it relative to the plane_3d
#ifdef SHARE
      shareA = Vertices->Share;
#endif

      Vertices = Vertices->Next;

      VerticesStart = Vertices;

      do
         {
         ptB    = Vertices->Vertex;
         sideB  = CalcSign(ptB, (*Root)->Poly);  // classify it relative to the plane_3d
#ifdef SHARE
         shareB = Vertices->Share;
#endif

#ifdef SHARE
// This disables sharing
//       if (shareB)
//          {
//          Vertices->Share->Share = NULL;
//             Vertices->Share = NULL;
//             shareB = NULL;
//          }
#endif

         if (sideB > epsilon2)  // if the current point_3d is on the positive side
            { // begin

#ifdef SHARE
            ThisPointClass = HC_OUT;
#endif
            if (PolyClass == HC_ON)        // if the polygon classification is on
               PolyClass = HC_OUT;         // classify the polygon as out
            else if (PolyClass != HC_OUT)  // else if the polygon classification is not out
               PolyClass = HC_SPANNING;    // set the polygon classification to spanning

            if (sideA < -epsilon2)         // if the previous point_3d was on the opposite side of the plane_3d
               { // begin
               Intersect((*Root)->Poly, ptA, ptB, pt);

#ifdef NOASM
               if (iPolyCount == POLYCOUNT)
                  {
                  char buffer[256];
                  sprintf(buffer,"SplitA: %08X ptA %6.3f %6.3f %6.3f %08X ptB %6.3f %6.3f %6.3f pt %6.3f %6.3f %6.3f", Vertices, ptA.x, ptA.y, ptA.z, Vertices->Prev, ptB.x, ptB.y, ptB.z, pt.x, pt.y, pt.z);
                  printfx(buffer);
                  }
#endif

               // if we are potentially on a shared seqment

#ifdef SHARE
               if (shareA && shareB)
                  {

                  // if we are on a shared segment
                  if (shareB->Next == shareA)
                     {
                     AddPoint(&VerticesIn, pt);
                     InsertPoint(shareB, pt);
                     VerticesIn->Prev->Share = shareB->Next;

                     AddPoint(&VerticesIn,  pt);
                     AddPoint(&VerticesOut, pt);

                     VerticesIn->Prev->Share = VerticesOut->Prev;
                     VerticesOut->Prev->Share = VerticesIn->Prev;

                     InsertPoint(shareB, pt);
                     AddPoint(&VerticesOut, pt);
                     VerticesOut->Prev->Share = shareB->Next;
                     }
                  else
                     {
                     AddPoint(&VerticesIn,  pt);
                     AddPoint(&VerticesOut, pt);

                     VerticesIn->Prev->Share = VerticesOut->Prev;
                     VerticesOut->Prev->Share = VerticesIn->Prev;
                     }
                  }
               else
#endif
                  {
                  AddPoint(&VerticesIn,  pt);
                  AddPoint(&VerticesOut, pt);

#ifdef SHARE
                  VerticesIn->Prev->Share = VerticesOut->Prev;
                  VerticesOut->Prev->Share = VerticesIn->Prev;
#endif
                  }
               PolyClass = HC_SPANNING; // set the PolyClass appropriately
               } // end

            AddPoint(&VerticesOut, ptB);

            // If old vertex was share copy it to the new poly (back link later)
#ifdef SHARE
            if (shareB)
               {
               VerticesOut->Prev->Share = shareB;
               }
#endif
            } // end
         else if (sideB < -epsilon2)  // the current point_3d is on the negative side
            { // begin

#ifdef SHARE
            ThisPointClass = HC_IN;
#endif
            if (PolyClass == HC_ON)      // if the polygon classification is on
               PolyClass = HC_IN;        // classify the polygon as out
            else if (PolyClass != HC_IN) // else if the polygon classification is not out
               PolyClass = HC_SPANNING;	 // set the polygon classification to spanning

            if (sideA > epsilon2) // if the previous point_3d was on the opposite side of the plane_3d
               { // begin
               Intersect((*Root)->Poly, ptA, ptB, pt);

#ifdef NOASM
               if (iPolyCount == POLYCOUNT)
                  {
                  char buffer[256];
                  sprintf(buffer,"SplitB: %08X ptA %6.3f %6.3f %6.3f %08X ptB %6.3f %6.3f %6.3f pt %6.3f %6.3f %6.3f", Vertices, ptA.x, ptA.y, ptA.z, Vertices->Prev, ptB.x, ptB.y, ptB.z, pt.x, pt.y, pt.z);
                  printfx(buffer);
                  }
#endif

               // if we are potentially on a shared seqment

#ifdef SHARE
               if (shareA && shareB)
                  {
                  // if we are on a shared segment

                  if (shareB->Next == shareA)
                     {
                     AddPoint(&VerticesOut, pt);
                     InsertPoint(shareB, pt);
                     VerticesOut->Prev->Share = shareB->Next;

                     AddPoint(&VerticesOut, pt);
                     AddPoint(&VerticesIn,  pt);

                     VerticesOut->Prev->Share = VerticesIn->Prev;
                     VerticesIn->Prev->Share = VerticesOut->Prev;

                     InsertPoint(shareB, pt);
                     AddPoint(&VerticesIn, pt);
                     VerticesIn->Prev->Share = shareB->Next;
		     }
                  else
                     {
                     AddPoint(&VerticesIn, pt);
                     AddPoint(&VerticesOut, pt);

                     VerticesIn->Prev->Share  = VerticesOut->Prev;
                     VerticesOut->Prev->Share = VerticesIn->Prev;
                     }
                  }
               else
#endif
                  {
                  AddPoint(&VerticesIn, pt);
                  AddPoint(&VerticesOut, pt);

#ifdef SHARE
                  VerticesIn->Prev->Share  = VerticesOut->Prev;
                  VerticesOut->Prev->Share = VerticesIn->Prev;
#endif
                  }

               PolyClass = HC_SPANNING; // set the PolyClass appropriately
               } // end

            AddPoint(&VerticesIn, ptB);

#ifdef SHARE
            if (shareB)
               {
               VerticesIn->Prev->Share = shareB;
               }
#endif
            } // end
         else // the current point_3d is on the plane_3d
            {
#ifdef SHARE
            ThisPointClass = HC_ON;

            if (shareB)
               {
#ifdef NOASM
               if (iPolyCount == POLYCOUNT)
                  {
                  char buffer[256];
                  sprintf(buffer,"ShareB: %08X ptB %6.3f %6.3f %6.3f", shareB, ptB.x, ptB.y, ptB.z);
                  printfx(buffer);
                  }
#endif
               // If we have previous point's IN or OUT classification

               if (LastInOutPointClass != HC_ON)
                  {
                  if (LastInOutPointClass == HC_OUT)
                     {
                     AddPoint(&VerticesIn, ptB);
                     AddPoint(&VerticesOut, ptB);

                     VerticesIn->Prev->Share = VerticesOut->Prev;
                     VerticesOut->Prev->Share = VerticesIn->Prev;

                     AddPoint(&VerticesOut, ptB);
#ifdef NOASM
                     shareB->Hack = 1;
#endif
                     VerticesOut->Prev->Share = shareB;
		     }
                  else // must be HC_IN
                     {
                     AddPoint(&VerticesOut, ptB);
                     AddPoint(&VerticesIn,  ptB);

                     VerticesOut->Prev->Share = VerticesIn->Prev;
                     VerticesIn->Prev->Share = VerticesOut->Prev;

                     AddPoint(&VerticesIn, ptB);
#ifdef NOASM
                     shareB->Hack = 1;
#endif
                     VerticesIn->Prev->Share = shareB;
                     }
                  }

               // Add both links and remove the wrong one later
               else
                  {
                  AddPoint(&VerticesIn, ptB);
                  AddPoint(&VerticesOut, ptB);

                  VerticesIn->Prev->Share = VerticesOut->Prev;
                  VerticesOut->Prev->Share = VerticesIn->Prev;

                  AddPoint(&VerticesOut, ptB);
                  AddPoint(&VerticesIn, ptB);
#ifdef NOASM
                  shareB->Hack = 2;
#endif
                  VerticesOut->Prev->Share = shareB;
                  VerticesIn->Prev->Share = shareB;
                  // if (DeferVerticesIn)
                  //    {
                  //    RemovePoint(DeferVerticesIn); // We don't handle queing these up
                  //    RemovePoint(DeferVerticesOut);
                  //    }
                  DeferVerticesOut = VerticesOut->Prev;
                  DeferVerticesIn = VerticesIn->Prev;
                  }

               LastInOutPointClass = HC_ON;
               }
            else
#endif
               {
               AddPoint(&VerticesIn, ptB);
               AddPoint(&VerticesOut, ptB);
#ifdef SHARE
               VerticesIn->Prev->Share  = VerticesOut->Prev;
               VerticesOut->Prev->Share = VerticesIn->Prev;
#endif
               }
            }

         ptA    = ptB;   // copy the current point_3d to the last point_3d
         sideA  = sideB; // copy the current point_3d's side information...

#ifdef SHARE
         shareA = shareB;

         if (ThisPointClass == HC_IN || ThisPointClass == HC_OUT)
            {
            LastInOutPointClass = ThisPointClass;

            // If we deferred we can clean up now
            if (DeferVerticesIn)
               {
               if (ThisPointClass == HC_IN)
                  {
                  RemovePoint(DeferVerticesOut);
                  }
               else
                  {
                  RemovePoint(DeferVerticesIn);
                  }

               DeferVerticesIn = NULL;
               DeferVerticesOut = NULL;
               }
            }
#endif

         Vertices = Vertices->Next;

         } while (Vertices != VerticesStart);

#ifdef NOASM
      if (DeferVerticesIn)
         {
         RemovePoint(DeferVerticesIn);
         RemovePoint(DeferVerticesOut);
         }
#endif
      switch (PolyClass) // perform the appropriate action based on the classification
         { // begin
         case HC_OUT: // if the polygon is entirely positive
            if (VerticesIn ) DisposeFalseShares(VerticesIn);
            if (VerticesOut) DisposeFalseShares(VerticesOut);
            if (VerticesIn ) DisposeVertices(VerticesIn);
            if (VerticesOut) DisposeVertices(VerticesOut);
            AddToBSPTree(Poly, &((*Root)->Outside));
            break; // end positive

         case HC_IN: // if the polygon is entirely negative
            if (VerticesIn ) DisposeFalseShares(VerticesIn);
            if (VerticesOut) DisposeFalseShares(VerticesOut);
            if (VerticesIn ) DisposeVertices(VerticesIn);
            if (VerticesOut) DisposeVertices(VerticesOut);
            AddToBSPTree(Poly, &((*Root)->Inside));
            break; // end negative

         case HC_SPANNING: // if the polygon was plane

//            if (iPolyCount == POLYCOUNT)
//               {
//               iPolyCount = iPolyCount*1;
//               }

            // Do all back share links now

#ifdef SHARE
            Vertices=VerticesIn;
            do
               {
               if (Vertices->Share) Vertices->Share->Share = Vertices;
               Vertices = Vertices->Next;
               } while (Vertices != VerticesIn);

            Vertices=VerticesOut;
            do
               {
               if (Vertices->Share) Vertices->Share->Share = Vertices;
               Vertices = Vertices->Next;
               } while (Vertices != VerticesOut);
#endif

#ifdef NOASM
            if (iPolyCount == POLYCOUNT)
               {
               Vertices=Poly->Vertices;
               do
                  {
                  char buffer[80];
                  sprintf(buffer,"Poly: %08X %6.3f %6.3f %6.3f %08X", Vertices, Vertices->Vertex.x, Vertices->Vertex.y, Vertices->Vertex.z, Vertices->Share);
                  printfx(buffer);
                  Vertices = Vertices->Next;
                  } while (Vertices != Poly->Vertices);

               Vertices=VerticesOut;
               Save2 = Vertices;
               do
                  {
                  char buffer[80];
                  sprintf(buffer," Out: %08X %6.3f %6.3f %6.3f %08X", Vertices, Vertices->Vertex.x, Vertices->Vertex.y, Vertices->Vertex.z, Vertices->Share);
                  printfx(buffer);
                  Vertices->Hack = 2;
                  Vertices = Vertices->Next;
                  } while (Vertices != VerticesOut);

               Vertices=VerticesIn;
               Save3 = Vertices;
               do
                  {
                  char buffer[80];
                  sprintf(buffer,"  In: %08X %6.3f %6.3f %6.3f %08X", Vertices, Vertices->Vertex.x, Vertices->Vertex.y, Vertices->Vertex.z, Vertices->Share);
                  printfx(buffer);
                  Vertices->Hack = 2;
                  Vertices = Vertices->Next;
                  } while (Vertices != VerticesIn);
               }

/*
               if (Save2)
                  {
                  Vertices=Save2;
                  do
                     {
                     char buffer[80];
                     sprintf(buffer," Out: %08X %6.3f %6.3f %6.3f %08X", Vertices, Vertices->Vertex.x, Vertices->Vertex.y, Vertices->Vertex.z, Vertices->Share);
                     printfx(buffer);
                     Vertices = Vertices->Next;
                     } while (Vertices != Save2);

                  Vertices=Save3;
                  do
                     {
                     char buffer[80];
                     sprintf(buffer,"  In: %08X %6.3f %6.3f %6.3f %08X", Vertices, Vertices->Vertex.x, Vertices->Vertex.y, Vertices->Vertex.z, Vertices->Share);
                     printfx(buffer);
                     Vertices = Vertices->Next;
                     } while (Vertices != Save3);

		}
*/
#endif

            polyA = new POLYGON;

            *polyA = *Poly;

            polyA->Vertices=VerticesIn;

            AddToBSPTree(polyA, &(*Root)->Inside);

            polyB = new POLYGON;

            *polyB = *Poly;

            polyB->Vertices=VerticesOut;

            AddToBSPTree(polyB, &(*Root)->Outside);

            DisposePolygon(Poly);
            break; // end spanning

         case HC_ON: // if the polygon was plane
            if (VerticesIn ) DisposeFalseShares(VerticesIn);
            if (VerticesOut) DisposeFalseShares(VerticesOut);
            if (VerticesIn ) DisposeVertices(VerticesIn);
            if (VerticesOut) DisposeVertices(VerticesOut);
            AddToBSPTree(Poly, &((*Root)->Outside));
            break; // end positive
         } // end
      }
   }

// Convert world coordinates to display coordinates
BOOL TThreeDSolid::WorldToDisplay(double x, double y, double z, POINT& disp)
   {
   double xc = (x * A1.x + A1.y * y + A1.z * z + Offset.x) * DVal;
   double yc = (x * A2.x + A2.y * y + A2.z * z + Offset.y) * DVal;
   double zc = (x * A3.x + A3.y * y + A3.z * z + Offset.z);

   if (zc == 0.0) return FALSE;

   double xm = xc /  zc;
   double ym = yc / -zc;

   if (xm >  1.0) return FALSE;
   else if (xm < -1.0) return FALSE;
   else if (ym >  1.0) return FALSE;
   else if (ym < -1.0) return FALSE;

//   disp.x = ((long) cut_error((A * xm + B))) + xoffset;
//   disp.y = ((long) cut_error((C * ym + D))) + yoffset;
   disp.x = ((long) g_round((A * xm + B))) + xoffset;
   disp.y = ((long) g_round((C * ym + D))) + yoffset;
//    disp.x = ((long) ((A * xm + B))) + xoffset;
//    disp.y = ((long) ((C * ym + D))) + yoffset;
   return TRUE;
   }

// Return the color to paint a polygon. Only ambient and diffuse
// lighting is used. You are looking at point p and the variable
// "normal" is the normal of the polygon. colorNdx specifies the
// desired color of the polygon.
COLORREF TThreeDSolid::ComputeColor(Point& p, VECTOR& normal, COLORREF colorNdx)
   {
   VECTOR l = Subtract(Light, p);  // Find vector from light to point p
   Normalize(l);
   double lDotN = Dot(l, normal);
   // Calculate diffuse lighting contribution to object's color
   if (lDotN <= 0) lDotN *= -Diffuse * NUM_SHADES;
   else lDotN *= Diffuse * NUM_SHADES;
   // Add ambient coefficient
   int Red   = (int)(GetRValue(colorNdx) + Ambient * NUM_SHADES + lDotN);
   int Green = (int)(GetGValue(colorNdx) + Ambient * NUM_SHADES + lDotN);
   int Blue  = (int)(GetBValue(colorNdx) + Ambient * NUM_SHADES + lDotN);
   if (Red   > 255) Red   = 255;
   if (Green > 255) Green = 255;
   if (Blue  > 255) Blue  = 255;
   return RGB(Red, Green, Blue);
   }

#define MAXVERT 4096

POINT t[MAXVERT];   // Screen coordinates of POLYGON to display

// Display the POLYGON
void TThreeDSolid::DisplayPolygon(POLYGON* Poly)
   {
   // PrecomputeCentroid(Poly);

   COLORREF color = ComputeColor(Poly->Centroid, Poly->Normal, Poly->ColorNdx);

   if (EnablePalette)
      {
      WORD palPrevNumEntries = MyLogPalette->palNumEntries;
      color = LoadColor(GetRValue(color), GetGValue(color), GetBValue(color));

      if (palPrevNumEntries != MyLogPalette->palNumEntries)
         {
         SelectPalette(MemDC, OldPalette, FALSE);
         OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
         RealizePalette(MemDC);
         }
      }

   VERTEXLIST * vertices = Poly->Vertices;

   int i = 0;
   do
      {
      if (!WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[i]))
         {
         i = 0;
         break;
         }
      if ((i < (MAXVERT-1)) && ((i == 0) || (t[i-1].x != t[i].x) || (t[i-1].y != t[i].y))) 
         {
         i++;
         }
      vertices = vertices->Next;
      } while (vertices != Poly->Vertices);

// t[i].x = t[0].x;
// t[i].y = t[0].y;    // Close off the POLYGON

#ifdef NOASMX
   HBRUSH hBrush = CreateSolidBrush(rand());
#else
   HBRUSH hBrush = CreateSolidBrush(color);
#endif
   HBRUSH oldBrush = (HBRUSH) SelectObject(MemDC, hBrush);

//if (Poly->ColorNdx != 0x000000FF)
   if (i > 2)
      {
      Polygon(MemDC, t, i);    // Display the POLYGON
      }

#ifdef NOASMX
   vertices = Poly->Vertices;

   do
      {
      if (vertices->Hack == 1)
         {
         WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[0]);
         t[0].x = t[0].x - 4 + (rand() % 9);
         t[0].y = t[0].y - 4 + (rand() % 9);
         SetPixel(MemDC, t[0].x  , t[0].y  , 0x0000FF00);
         SetPixel(MemDC, t[0].x  , t[0].y+1, 0x0000FF00);
         SetPixel(MemDC, t[0].x+1, t[0].y  , 0x0000FF00);
         SetPixel(MemDC, t[0].x  , t[0].y-1, 0x0000FF00);
         SetPixel(MemDC, t[0].x-1, t[0].y  , 0x0000FF00);
         }
      else if (vertices->Hack == 2)
         {
         WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[0]);
         t[0].x = t[0].x - 4 + (rand() % 9);
         t[0].y = t[0].y - 4 + (rand() % 9);
         SetPixel(MemDC, t[0].x  , t[0].y  , 0x000000FF);
         for (i=0;i<=1;i++)
            {
            SetPixel(MemDC, t[0].x  , t[0].y+i, 0x000000FF);
            SetPixel(MemDC, t[0].x+i, t[0].y  , 0x000000FF);
            SetPixel(MemDC, t[0].x  , t[0].y-i, 0x000000FF);
            SetPixel(MemDC, t[0].x-i, t[0].y  , 0x000000FF);
            }
         }
      else if (vertices->Share)
         {
         WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[0]);
         t[0].x = t[0].x - 4 + (rand() % 9);
         t[0].y = t[0].y - 4 + (rand() % 9);
         SetPixel(MemDC, t[0].x  , t[0].y  , 0x00FF0000);
         SetPixel(MemDC, t[0].x  , t[0].y+1, 0x00FF0000);
         SetPixel(MemDC, t[0].x+1, t[0].y  , 0x00FF0000);
         SetPixel(MemDC, t[0].x  , t[0].y-1, 0x00FF0000);
         SetPixel(MemDC, t[0].x-1, t[0].y  , 0x00FF0000);
         }
      else
         {
         WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[0]);
         t[0].x = t[0].x - 4 + (rand() % 9);
         t[0].y = t[0].y - 4 + (rand() % 9);
         SetPixel(MemDC, t[0].x  , t[0].y  , 0x00FFFFFF);
         SetPixel(MemDC, t[0].x  , t[0].y+1, 0x00FFFFFF);
         SetPixel(MemDC, t[0].x+1, t[0].y  , 0x00FFFFFF);
         SetPixel(MemDC, t[0].x  , t[0].y-1, 0x00FFFFFF);
         SetPixel(MemDC, t[0].x-1, t[0].y  , 0x00FFFFFF);
         }
      vertices = Vertices->Next;
      } while (vertices != Poly->Vertices);
#endif

// NormalPen.lopnColor = color;
// NormalPen.lopnWidth.x = 0;

// HPEN hPen = CreatePenIndirect(&NormalPen);
// OldPen = (HPEN) SelectObject(MemDC, hPen);

// Polyline(MemDC, t, i);

// SelectObject(MemDC, OldPen);

   SelectObject(MemDC, oldBrush);
   DeleteObject(hBrush);

// DeleteObject(hPen);
   }

// Display the figure stored in the BSP tree
void TThreeDSolid::View()
   {
   erase_screen();

   ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);

   // memory

   MemDC = CreateCompatibleDC(ScreenDC);
   HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
      RealizePalette(MemDC);
      }

   // Create the correct brush and display the POLYGON
   HPEN hOldpen = HPEN(SelectObject(MemDC, GetStockObject(NULL_PEN)));

//   int OldFillMode = SetPolyFillMode(MemDC, WINDING);

   TraverseTree(Tree);

   SelectObject(MemDC, hOldpen);

   if (EnablePalette)
      {
      SelectPalette(MemDC, OldPalette, FALSE);
      }

   SelectObject(MemDC, oldBitmap);

   DeleteDC(MemDC);
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);

   MainWindowx->ScreenWindow->Invalidate(FALSE);
   }

// Traverse a BSP tree, rendering a three-dimensional scene
void TThreeDSolid::TraverseTree(BSPNode* tree)
   {
   double d;

   if (tree)
      {
      TraverseTree_s.x = From.x - tree->Poly->Vertices->Vertex.x;
      TraverseTree_s.y = From.y - tree->Poly->Vertices->Vertex.y;
      TraverseTree_s.z = From.z - tree->Poly->Vertices->Vertex.z;
      Normalize(TraverseTree_s);
      d = Dot(TraverseTree_s, tree->Poly->Normal);

      if (d > 0.0 /* epsilon3 */)
         { // The eye is in front
         TraverseTree(tree->Inside);	// of the polygon
         DisplayPolygon(tree->Poly);
         TraverseTree(tree->Outside);
         }
      else /* if (d < -epsilon3) */
         { // The eye is in back
         TraverseTree(tree->Outside); // of the polygon
         DisplayPolygon(tree->Poly);
         TraverseTree(tree->Inside);
         }
/*
      else
         { // The eye is in on
//	 TraverseTree(tree->Outside); // of the polygon
//	 TraverseTree(tree->Inside);
	}
*/
      }
   }

