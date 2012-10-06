#ifndef __COLORDLG_H
#define __COLORDLG_H

#include <owl\control.h>
#include <owl\dialog.h>
#include <owl\scrollba.h>

class TColorControl : public TControl
{
 public:
    TColorControl(TWindow * Parent, UINT ResourceId, const TColor & Color);

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
};

class TColorDialog : public TDialog
{
 public:
    TColorDialog(
        TWindow            *   Parent,
        const TColor         & InitialColor,
        const char         *   Caption,
        const char         *   LogoCommand,
        class TColorDialog * & ExternalReference
        );

    const TColor & GetSelectedColor() const;

 protected:
    TScrollBar       m_ColorBar1;
    TScrollBar       m_ColorBar2;
    TScrollBar       m_ColorBar3;
    TColorControl    m_SelColor;
    const char   *   m_LogoCommand;
    TColorDialog * & m_ExternalReference;

    void SetupWindow();

    void UpdateBars(const TColor & NewColor);

    void ClickControl1();
    void ClickControl2();
    void ClickControl3();
    void ClickControl4();
    void ClickControl5();
    void ClickControl6();
    void ClickControl7();
    void ClickControl8();
    void SetColorFromControl(UINT Id);
    void SetColorFromSlider();
    void EvVScroll(uint scrollCode, uint thumbPos, HWND hWndCtl);
    void EvHScroll(uint scrollCode, uint thumbPos, HWND hWndCtl);

    void CmOk();
    void DoApply(UINT);
    void EvDestroy();

    DECLARE_RESPONSE_TABLE(TColorDialog);
};

#endif // __COLORDLG_H
