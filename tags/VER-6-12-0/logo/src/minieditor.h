#ifndef _MINIEDITOR_H_
#define _MINIEDITOR_H_

#include "editwnd.h"

class TMiniEditorRichEdit : public TRichEditWithPopup
   {
 public:
   TMiniEditorRichEdit(TWindow * Parent);

 protected:
   bool CanClose()
      {
      return true;
      }
   };

class TMiniEditor : public TDialog
   {
 public:
   TMiniEditor(
      TWindow    * Parent,
      const char * ToLine
      );
   ~TMiniEditor();

   const char * GetText();

 protected:
   void EvSetFocus(HWND);
   void CmSelectAll();

   void SetupWindow();
   void CmOk();
   void EvSize(UINT arg1, TSize & arg2);

 private:
   void RecalculateLayout();

   TMiniEditorRichEdit m_TextField;
   TEdit               m_ToLine;
   TButton             m_EndButton;

   char *   m_ToLineString;

   char *   m_EditorContents;
   size_t   m_EditorContentsLength;

 private:
   DECLARE_RESPONSE_TABLE(TMiniEditor);
   };

#endif // _MINIEDITOR_H_
