//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//----------------------------------------------------------------------------
#ifndef __SIZEDLG_H
#define __SIZEDLG_H

class TSizeControl : public TControl
   {
   public:
   TSizeControl(TWindow* parent, int resId, TColor size);
   virtual void SetSize(TColor size);
   TColor GetSize() const
      {
      return Size;
      }

   private:
   TColor Size;

   char far* GetClassName()
      {
      return "SizeControl";
      }

   UINT Transfer(void* buffer, TTransferDirection direction);

   void EvPaint();

   void EvLButtonDown(UINT, TPoint&);
   void EvLButtonDblClk(UINT, TPoint&);

   DECLARE_RESPONSE_TABLE(TSizeControl);
   }
;

class TSizeDialog : public TDialog
   {
   public:
   TSizeDialog(TWindow* parent, TColor& size, char *caption);

   protected:
   TScrollBar*   SizeBar;
   TSizeControl* SelSize;
   char *sizecaption;

   void SetupWindow();
   void TransferData(TTransferDirection direction);

   virtual void UpdateBars(TColor size);

   void ClickFmControl1();
   void ClickFmControl2();
   void ClickFmControl3();
   void ClickFmControl4();
   void ClickFmControl5();
   void ClickFmControl6();
   void ClickFmControl7();
   void ClickFmControl8();
   void SetSizeFmControl(UINT Id);
   void SetSizeFmSlider();

   DECLARE_RESPONSE_TABLE(TSizeDialog);
   }
;

#endif
