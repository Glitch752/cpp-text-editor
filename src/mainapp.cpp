#include "./mainapp.h"
#include <wx/wx.h>

MainApp::MainApp(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 560)) {
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
    editMenu->Append(wxID_REDO);
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
}

void MainApp::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "Any file|*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    // TODO: Implement
}

void MainApp::OnSave(wxCommandEvent& event) {

}

void MainApp::OnSaveAs(wxCommandEvent& event) {

}

void MainApp::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainApp::OnUndo(wxCommandEvent& event) {

}

void MainApp::OnRedo(wxCommandEvent& event) {

}

void MainApp::OnCut(wxCommandEvent& event) {

}

void MainApp::OnCopy(wxCommandEvent& event) {

}

void MainApp::OnPaste(wxCommandEvent& event) {

}

void MainApp::OnDelete(wxCommandEvent& event) {

}

void MainApp::OnSelectAll(wxCommandEvent& event) {

}

void MainApp::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A simple text editor to learn about GUI applications in C++.", "About", wxOK | wxICON_INFORMATION);
}

void MainApp::OnNew(wxCommandEvent& event) {
    
}