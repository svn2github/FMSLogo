//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//   Definition of class TFileWindow.  This defines the OWL 1.0 compatible
//   file edit window
//----------------------------------------------------------------------------
#ifndef __FILEWND_H
#define __FILEWND_H


//
//  class TFileWindow
//  ----- -----------
//
class TFileWindow : public TEditWindow
   {
 public:
   char *FileName;
   bool IsNewFile;

   TFileWindow(
      TWindow *        parent,
      const char far * title,
      const char far * fileName,
      TModule * module = 0
   );

   ~TFileWindow();

   virtual bool CanClear();
   virtual bool CanClose()
      {
      return CanClear();
      }

   void NewFile();
   void Open();
   bool Read(const char * fileName = 0);
   void ReplaceWith(const char * filename);
   bool Save();
   bool SaveAs();
   void SetFileName(const char * filename);
   bool Write(const char * fileName = 0);

 protected:
   //
   // menu command response functions
   //
   void CmFileNew()
      {
      NewFile();
      }                             // CM_FILENEW

   void CmFileOpen()
      {
      Open();
      }                             // CM_FILEOPEN

   void CmFileSave()
      {
      Save();
      }                             // CM_FILESAVE

   void CmFileSaveAs()
      {
      SaveAs();
      }                             // CM_FILESAVEAS

   virtual void SetupWindow();

   DECLARE_RESPONSE_TABLE(TFileWindow);
   DECLARE_STREAMABLE(_EXPCLASS, TFileWindow, 1);
   }
;

#endif // __FILEWND_H

