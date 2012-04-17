#include "logocodectrl.h"
#include "localizedstrings.h"
#include "logocore.h"  // for ARRAYSIZE
#include "screenwindow.h"  // for TraceOutput

#include "scintilla/include/SciLexer.h"
#include "scintilla/include/Scintilla.h"

BEGIN_EVENT_TABLE(CLogoCodeCtrl, wxStyledTextCtrl)
    EVT_STC_UPDATEUI(wxID_ANY, CLogoCodeCtrl::OnUpdateUi)
END_EVENT_TABLE()

CLogoCodeCtrl::CLogoCodeCtrl(
    wxWindow *      Parent,
    wxWindowID      Id
    ) : wxStyledTextCtrl(Parent, Id)
{
    // Hide the margin that Scintilla creates by default.
    // We don't use it for anything, so it just looks weird.
    SetMarginWidth(1, 0);

    // Switch to the FMSLogo style
    StyleClearAll();
    SetLexer(SCLEX_FMSLOGO);
    Colourise(0, -1);

    // override the CTRL+<LETTER> sequences to do nothing so that they
    // don't insert control characters.
    for (int i = 0; i < 26; i++)
    {
        // I'm not sure why, but CTRL+Y for "Redo" is special and if
        // we set the handler to SCI_NULL, it stops working.
        const int key = 'A' + i;
        if (key != 'Y')
        {
            CmdKeyAssign(key, wxSTC_SCMOD_CTRL, 0);
        }
    }
}

void
CLogoCodeCtrl::SetFont(wxFont & font)
{
    // Set the font
    StyleSetFont(STYLE_DEFAULT, font);

    // Apply the font
    StyleClearAll();

    const wxColor black     = RGB(0,0,0);
    const wxColor white     = RGB(0XFF, 0XFF, 0XFF);
    const wxColor darkgreen = RGB(0,    0x80, 0);
    const wxColor darkred   = RGB(0x80,    0, 0);
    const wxColor red       = RGB(0xFF,    0, 0);
    const wxColor lightgrey = RGB(0xCC, 0xCC, 0xCC);
    const wxColor lightblue = RGB(200,   242, 255);
    const wxColor darkblue  = RGB(  0,    0,  0x80);

    StyleSetForeground(SCE_FMS_COMMENT,          darkgreen);
    StyleSetForeground(SCE_FMS_COMMENTBACKSLASH, darkgreen);
    StyleSetForeground(SCE_FMS_STRING,         darkred);
    StyleSetForeground(SCE_FMS_STRING_VBAR,    darkred);

    StyleSetForeground(SCE_FMS_VARIABLE,       darkblue);
    StyleSetForeground(SCE_FMS_VARIABLE_VBAR,  darkblue);

    StyleSetForeground(STYLE_BRACELIGHT,    darkgreen);
    StyleSetBackground(STYLE_BRACELIGHT,    lightblue);

    StyleSetForeground(STYLE_BRACEBAD,      red);
    StyleSetBackground(STYLE_BRACEBAD,      lightblue);
}

bool
CLogoCodeCtrl::IsTextSelected()
{
    // Get whatever is selected
    int selectionStart = -1;
    int selectionEnd   = -1;
    GetSelection(&selectionStart, &selectionEnd);

    // Determine if the selection is non-empty
    return selectionStart != selectionEnd;
}

static bool IsParen(int Char)
{
    switch (Char)
    {
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
        return true;
    }

    return false;
}

void
CLogoCodeCtrl::FindMatchingParen(
    int & CurrentParenPosition,
    int & MatchingParenPosition
    )
{
    CurrentParenPosition  = INVALID_POSITION;
    MatchingParenPosition = INVALID_POSITION;

    int currentPosition = GetCurrentPos();
    int currentChar     = GetCharAt(currentPosition);
    if (IsParen(currentChar))
    {
        // we're close enough to a paren to try to match it
        int matchingParenPosition = BraceMatch(currentPosition);
        if (matchingParenPosition != INVALID_POSITION)
        {
            // found a match

            // If the paren after the caret is an open paren, then
            // the matching paren will be after it.  In this case, 
            // we want to jump just after the matching paren's position
            // to remain on the outside of the parens.
            // Likewise, if the paren after the caret is a close paren,
            // then the matching paren will be before it.  In this case,
            // we also want to jump after the matching paren's position
            // so that we can remain on the inside of the parens.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = matchingParenPosition + 1;
        }
        else
        {
            // If paren after the caret has no matching paren,
            // then mark it as a bad paren, instead of trying to
            // match the one before the caret.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = INVALID_POSITION;
        }
    }
    else
    {
        // we're not over a paren, so try the position just before the caret
        if (currentPosition != 0)
        {
            int previousChar = GetCharAt(currentPosition - 1);
            if (IsParen(previousChar))
            {
                // we're close enough to a paren to try to match it
                int matchingParenPosition = BraceMatch(currentPosition - 1);
                if (matchingParenPosition != INVALID_POSITION)
                {
                    // found a match

                    // If the paren before the caret is an open paren, then
                    // the matching paren will be after it.  In this case, 
                    // we want to jump to the matching paren's position to
                    // remain on the inside of the parens.
                    // Likewise, if the paren before the caret is a close paren,
                    // then the matching paren will be before it.  In this case,
                    // we also want to jump after the matching paren's position
                    // so that we can remain on the outside of the parens.
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = matchingParenPosition;
                }
                else
                {
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = INVALID_POSITION;
                }
            }
        }
    }
}

// Moves the caret to the matching parent, bracket, if the caret is
// currently adject to a paren, bracket, etc. 
void CLogoCodeCtrl::FindMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION)
    {
        GotoPos(matchingParenPosition);
    }
}

// Moves the caret to the matching parent, bracket, if the caret is
// currently adject to a paren, bracket, etc.  Also selects the entire
// text within the parens.
void CLogoCodeCtrl::SelectMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION && currentParenPosition != INVALID_POSITION)
    {
        // Found a match.  Jump to it.
        SetAnchor(GetCurrentPos());
        SetCurrentPos(matchingParenPosition);
        ScrollCaret();
    }
}


// Sends SCI_SCROLLCARET because wxStyledTextCtrl doesn't export this wrapper.
// TODO: Submit a patch to wxWidgets to add this.
void CLogoCodeCtrl::ScrollCaret()
{
    SendMsg(SCI_SCROLLCARET);
}

void CLogoCodeCtrl::OnUpdateUi(wxStyledTextEvent& Event)
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (currentParenPosition != INVALID_POSITION)
    {
        // We're close enough to a paren to try to match it
        if (matchingParenPosition != INVALID_POSITION)
        {
            // found a match
            if (currentParenPosition == GetCurrentPos())
            {
                BraceHighlight(currentParenPosition, matchingParenPosition - 1);
            }
            else
            {
                BraceHighlight(currentParenPosition, matchingParenPosition);
            }
        }
        else
        {
            // didn't find a match
            BraceBadLight(currentParenPosition);
        }
    }
    else
    {
        // We're not adacent to a paren, so remove the paren highlighting.
        BraceBadLight(INVALID_POSITION);
        BraceHighlight(INVALID_POSITION, INVALID_POSITION);
    }
}

void
CLogoCodeCtrl::SetScintillaSearchFlags(
    wxFindReplaceFlags WxSearchFlags
    )
{
    // Map the wxWidgets flags to the Scintilla flags
    int scintillaSearchFlags = 0;
    
    if (WxSearchFlags & wxFR_MATCHCASE)
    {
        scintillaSearchFlags |= SCFIND_MATCHCASE;
    }
    if (WxSearchFlags & wxFR_WHOLEWORD)
    {
        scintillaSearchFlags |= SCFIND_WHOLEWORD;
    }

    // Set the scintilla search flags.
    SetSearchFlags(scintillaSearchFlags);
}

void
CLogoCodeCtrl::DoSearchOperation(
    SEARCH_OPERATION   SearchOperation,
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    // Configure Scintilla to search as requested
    SetScintillaSearchFlags(WxSearchFlags);

    if (SearchOperation == SEARCH_OPERATION_FindAndReplace)
    {
        // We are doing a find&replace operation.
        // If the string to be replaced is currently selected, then replace it.
        // After the replacement is performed, search for the next occurence.
        const wxString & selectedText = GetSelectedText();

        // Now figure out what to do with it.
        int cmp;
        if (WxSearchFlags & wxFR_MATCHCASE)
        {
            // Do a case-sensitive comparison
            cmp = selectedText.Cmp(StringToFind);
        }
        else
        {
            // Do a case-insensitive comparison
            cmp = selectedText.CmpNoCase(StringToFind);
        }

        if (cmp == 0)
        {
            // This is a match.  Replace the string.
            int selectionStart = GetSelectionStart();
            int selectionEnd   = GetSelectionEnd();

            // Move the target to the selection
            SetTargetStart(selectionStart);
            SetTargetEnd(selectionEnd);

            // Perform the replacement
            ReplaceTarget(ReplacementString);

            // Update the selection to be what we just inserted.
            SetSelection(
                selectionStart,
                selectionStart + ReplacementString.Length());
        }
    }

    // Now search for the next occurance
    if (WxSearchFlags & wxFR_DOWN)
    {
        // We're searching down, so the range goes from the
        // current position to the end.
        SetTargetStart(GetSelectionEnd());
        SetTargetEnd(GetTextLength());
    }
    else
    {
        // We're searching up, so the range goes from the
        // current position to the beginning.
        SetTargetStart(GetSelectionStart());
        SetTargetEnd(0);
    }

    // Perform the search.
    int location = SearchInTarget(StringToFind);
    if (location != -1)
    {
        // Found it.  Select the string.
        SetSelection(location, location + StringToFind.Length());
    }
    else
    {
        // Notify the user that we were unable to find it.
        const wxString & notFoundMessage = wxString::Format(
            LOCALIZED_STRINGTABLE_CANNOTFINDSTRING,
            StringToFind.c_str());

        ::wxMessageBox(
            notFoundMessage,
            LOCALIZED_GENERAL_PRODUCTNAME,
            MB_ICONWARNING | MB_OK,
            this);
    }
}

void
CLogoCodeCtrl::Find(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind
    )
{
    DoSearchOperation(
        SEARCH_OPERATION_Find,
        WxSearchFlags,
        StringToFind,
        wxEmptyString);
}

void
CLogoCodeCtrl::Replace(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    DoSearchOperation(
        SEARCH_OPERATION_FindAndReplace,
        WxSearchFlags,
        StringToFind,
        ReplacementString);
}

void
CLogoCodeCtrl::ReplaceAll(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    // Configure Scintilla to search as requested
    SetScintillaSearchFlags(WxSearchFlags);

    // The user selected "Replace All", so the selection
    // goes from the beginning to the end of the document.
    SetTargetStart(0);
    SetTargetEnd(GetTextLength());

    int location = SearchInTarget(StringToFind);
    while (location != -1)
    {
        // Found it. Replace the string
        ReplaceTarget(ReplacementString);

        // Move the selection so that we can repeat the search
        SetTargetStart(location + ReplacementString.Length());
        SetTargetEnd(GetTextLength());

        // Repeat the search
        location = SearchInTarget(StringToFind);
    }
}
