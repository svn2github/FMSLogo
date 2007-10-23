// -*- c++ -*-

#include "wx/app.h"

const int DEFAULT_COMMANDER_HEIGHT = 150;
const int MIN_COMMANDER_HEIGHT     = 110;
const int DEFAULT_SPLITTER_WIDTH   = 5;

class CFmsLogo : public wxApp
{
public:
    CFmsLogo();

    virtual bool OnInit();

    DECLARE_NO_COPY_CLASS(CFmsLogo)
};
