#pragma once
#include <wx/wx.h>
#include "wx/stc/stc.h"

class MainApp : public wxFrame {
    public:
        MainApp(const wxString& title);
    protected:
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);

        void OnUndo(wxCommandEvent& event);
        void OnRedo(wxCommandEvent& event);
        void OnCut(wxCommandEvent& event);
        void OnCopy(wxCommandEvent& event);
        void OnPaste(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
        void OnFind(wxCommandEvent& event);
        void OnReplace(wxCommandEvent& event);
        void OnSelectAll(wxCommandEvent& event);

        void OnAbout(wxCommandEvent& event);
    private:
        wxStyledTextCtrl *styledTextCtrl;
        wxString savePath = "";
};