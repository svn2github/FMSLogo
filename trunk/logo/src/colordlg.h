#ifndef __COLORDLG_H
#define __COLORDLG_H

class TColorControl : public TControl
   {
 public:
   TColorControl(TWindow * Parent, int ResourceId, const TColor & Color);

   void SetColor(const TColor & NewColor);
   const TColor & GetColor() const
      {
      return m_Color;
      }

 private:
   TColor m_Color;

 protected:

   char *GetClassName()
      {
      return "ColorControl";
      }

   void EvPaint();

   void EvLButtonDown(UINT, TPoint &);
   void EvLButtonDblClk(UINT, TPoint &);

   DECLARE_RESPONSE_TABLE(TColorControl);
   }
;

class TColorDialog : public TDialog
   {
 public:
   TColorDialog(TWindow * Parent, const TColor & InitialColor, const char *Caption);
   const TColor & GetSelectedColor() const;

 protected:
   TScrollBar    m_ColorBar1;
   TScrollBar    m_ColorBar2;
   TScrollBar    m_ColorBar3;
   TColorControl m_SelColor;

   void SetupWindow();

   void UpdateBars(const TColor & NewColor);

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

