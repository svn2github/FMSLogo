// -*- c++ -*-

#ifndef __SIZEDLG_H
#define __SIZEDLG_H

#include <owl/control.h>
#include <owl/dialog.h>
#include <owl/scrollba.h>

class TSizeControl : public TControl
{
public:
    TSizeControl(TWindow* parent, int resId, const TSize & Size);
    void SetSize(const TSize & NewSize);

    const TSize & GetSize() const
    {
        return m_Size;
    }

private:
    TSize m_Size;

    char * GetClassName()
    {
        return "SizeControl";
    }

    void EvPaint();

    void EvLButtonDown(UINT, TPoint&);
    void EvLButtonDblClk(UINT, TPoint&);

    DECLARE_RESPONSE_TABLE(TSizeControl);
};

class TSizeDialog : public TDialog
{
public:
    TSizeDialog(TWindow* Parent, const TSize & InitialSize, TSizeDialog * &);
    const TSize & GetSelectedSize() const;

private:
    TScrollBar      m_SizeBar;
    TSizeControl    m_SelSize;
    TSizeDialog * & m_ExternalReference;

protected:
    void SetupWindow();

    void UpdateBars(const TSize & Size);

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

    void CmOk();
    void DoApply(UINT);
    void EvDestroy();
    void EvVScroll(uint scrollCode, uint thumbPos, HWND hWndCtl);

    DECLARE_RESPONSE_TABLE(TSizeDialog);
};

#endif // __SIZEDLG_H
