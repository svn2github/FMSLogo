#include "LexFmsLogoRegisterer.h"

#include <stddef.h>

#include "ILexer.h"
#include "LexerModule.h"
#include "Catalogue.h"

extern LexerModule lmFmsLogo; // defined in LexFmsLogo.cxx

// Registers the lexer that's implemented in LexFmsLogo.cxx.
// While this function could be implemented within that file and possibly
// invoked automatically, none of the lexers that are defined within Scintilla
// register themselves, so for symmetry, this is done externally.
void RegisterFmslogoLexer()
{
    static bool s_IsRegistered = false;

    if (!s_IsRegistered)
    {
        Catalogue::AddLexerModule(&lmFmsLogo);
        s_IsRegistered = true;
    }
}
