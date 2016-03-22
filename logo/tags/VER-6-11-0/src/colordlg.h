//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//----------------------------------------------------------------------------
#ifndef __COLORDLG_H
#define __COLORDLG_H

class TColorControl : public TControl
   {
 public:
   TColorControl(TWindow * parent, int resId, TColor color);
   virtual void SetColor(TColor color);
   const TColor GetColor() const
      {
      return Color;
      }

 private:
   TColor Color;

   char *GetClassName()
      {
      return "ColorControl";
      }

   UINT Transfer(void *buffer, TTransferDirection direction);

 protected:
   void EvPaint();

   void EvLButtonDown(UINT, TPoint &);
   void EvLButtonDblClk(UINT, TPoint &);

   DECLARE_RESPONSE_TABLE(TColorControl);
   }
;

class TColorDialog : public TDialog
   {
 public:
   TColorDialog(TWindow * parent, TColor & color, const char *caption);

 protected:
   TScrollBar *ColorBar1;
   TScrollBar *ColorBar2;
   TScrollBar *ColorBar3;
   TColorControl *SelColor;
   const char *colorcaption;

   void SetupWindow();
   void TransferData(TTransferDirection direction);

   virtual void UpdateBars(TColor color);

   void ClickFmControl1();
   void ClickFmControl2();
   void ClickFmControl3();
   void ClickFmControl4();
   void ClickFmControl5();
   void ClickFmControl6();
   void ClickFmControl7();
   void ClickFmControl8();
   void SetColorFmControl(UINT Id);
   void SetColorFmSlider();

   DECLARE_RESPONSE_TABLE(TColorDialog);
   }
;

#endif // __COLORDLG_H


