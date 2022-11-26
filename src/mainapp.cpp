#include "./mainapp.h"
#include <wx/wx.h>
#include "wx/richtext/richtextctrl.h"
#include <wx/richtext/richtextbuffer.h>

MainApp::MainApp(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize().Scale(0.50, 0.75)) {
    wxImage::AddHandler(new wxXPMHandler);

    wxIcon icon(wxT("./tempIcon.xpm"), wxBITMAP_TYPE_XPM);
    SetIcon(icon);

    // Center();

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu *editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO, _("&Redo\tCtrl+Y")); // The default keybind is Ctrl+Shift+Z, but I changed it to Ctrl+Y
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_PASTE);
    editMenu->Append(wxID_DELETE);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_SELECTALL);

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(editMenu, wxT("&Edit"));
    menuBar->Append(helpMenu, wxT("&Help"));

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainApp::OnNew,       this, wxID_NEW      );
    Bind(wxEVT_MENU, &MainApp::OnOpen,      this, wxID_OPEN     );
    Bind(wxEVT_MENU, &MainApp::OnSave,      this, wxID_SAVE     );
    Bind(wxEVT_MENU, &MainApp::OnSaveAs,    this, wxID_SAVEAS   );
    Bind(wxEVT_MENU, &MainApp::OnExit,      this, wxID_EXIT     );
    Bind(wxEVT_MENU, &MainApp::OnUndo,      this, wxID_UNDO     );
    Bind(wxEVT_MENU, &MainApp::OnRedo,      this, wxID_REDO     );
    Bind(wxEVT_MENU, &MainApp::OnCut,       this, wxID_CUT      );
    Bind(wxEVT_MENU, &MainApp::OnCopy,      this, wxID_COPY     );
    Bind(wxEVT_MENU, &MainApp::OnPaste,     this, wxID_PASTE    );
    Bind(wxEVT_MENU, &MainApp::OnDelete,    this, wxID_DELETE   );
    Bind(wxEVT_MENU, &MainApp::OnSelectAll, this, wxID_SELECTALL);
    Bind(wxEVT_MENU, &MainApp::OnAbout,     this, wxID_ABOUT    );

	richTextCtrl = new wxRichTextCtrl(this);
}

void MainApp::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "Any file|*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = openFileDialog.GetPath();
    richTextCtrl->LoadFile(path, wxRICHTEXT_TYPE_TEXT);
}

void MainApp::OnSaveAs(wxCommandEvent& event) {
	wxFileDialog saveFileDialog(this, _("Enter a filename"), "", "", "Any file|*", wxFD_SAVE|wxFD_FILE_MUST_EXIST);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString path = saveFileDialog.GetPath();
    richTextCtrl->SaveFile(path);
}

void MainApp::OnSave(wxCommandEvent& event) {
    // Make sure the file we're saving to exists
    if (richTextCtrl->GetFilename().empty()) {
        OnSaveAs(event);
    } else {
        richTextCtrl->SaveFile();
    }
}

void MainApp::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainApp::OnUndo(wxCommandEvent& event) {
    richTextCtrl->Undo();
}

void MainApp::OnRedo(wxCommandEvent& event) {
    richTextCtrl->Redo();
}

void MainApp::OnCut(wxCommandEvent& event) {
    richTextCtrl->Cut();
}

void MainApp::OnCopy(wxCommandEvent& event) {
    richTextCtrl->Copy();
}

void MainApp::OnPaste(wxCommandEvent& event) {
    richTextCtrl->Paste();
}

void MainApp::OnDelete(wxCommandEvent& event) {
    richTextCtrl->DeleteSelection();
}

void MainApp::OnSelectAll(wxCommandEvent& event) {
    richTextCtrl->SelectAll();
}

void MainApp::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A simple text editor to learn about GUI applications in C++.", "About", wxOK | wxICON_INFORMATION);
}

void MainApp::OnNew(wxCommandEvent& event) {
    richTextCtrl->Clear();
}