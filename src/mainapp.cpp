#include "./mainapp.h"
#include <wx/wx.h>
#include "wx/stc/stc.h"

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
    editMenu->Append(wxID_FIND);
    editMenu->Append(wxID_REPLACE);
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
    Bind(wxEVT_MENU, &MainApp::OnFind,      this, wxID_FIND     );
    Bind(wxEVT_MENU, &MainApp::OnReplace,   this, wxID_REPLACE  );
    Bind(wxEVT_MENU, &MainApp::OnSelectAll, this, wxID_SELECTALL);
    Bind(wxEVT_MENU, &MainApp::OnAbout,     this, wxID_ABOUT    );

    // Add a box in the middle of the screen for find and replace operations

    // 1. Create a sizer to hold the find and replace boxes
    findReplaceSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *findSizer = new wxBoxSizer(wxHORIZONTAL);
    // Find text
    findSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Find: ")), 0, wxALIGN_CENTER);
    // Input for the text to find
    findSizer->Add(new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(200, -1)));
    // Checkbox for case sensitivity
    findSizer->Add(new wxCheckBox(this, wxID_ANY, wxT("Case sensitive")));
    // Checkbox for whole word
    findSizer->Add(new wxCheckBox(this, wxID_ANY, wxT("Whole word")));
    // Checkbox for regular expression
    findSizer->Add(new wxCheckBox(this, wxID_ANY, wxT("Regular expression")));
    // Button for find next
    findSizer->Add(new wxButton(this, wxID_ANY, wxT("Find next")));
    // Button for find previous
    findSizer->Add(new wxButton(this, wxID_ANY, wxT("Find previous")));

    findReplaceSizer->Add(findSizer, 0, wxALIGN_TOP);

    replaceSizer = new wxBoxSizer(wxHORIZONTAL);

    // Checkbox for replace
    replaceSizer->Add(new wxCheckBox(this, wxID_ANY, wxT("Replace")));
    // Input for the text to replace
    replaceSizer->Add(new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(200, -1)));
    // Button for replace next
    replaceSizer->Add(new wxButton(this, wxID_ANY, wxT("Replace")));
    // Button for replace all
    replaceSizer->Add(new wxButton(this, wxID_ANY, wxT("Replace all")));

    findReplaceSizer->Add(replaceSizer, wxALIGN_BOTTOM);

    // Close button
    wxButton *closeButton = new wxButton(this, wxID_ANY, wxT("Close"));
    findReplaceSizer->Add(closeButton);

    // Bind the close button to a function
    closeButton->Bind(wxEVT_BUTTON, &MainApp::OnCloseFindReplace, this);

    replaceSizer->Show(false);
    findReplaceSizer->Show(false);

    // Make the findReplaceSizer centered in the middle of the screen
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(findReplaceSizer, 0, wxALIGN_CENTER);
    
    // Make the mainSizer fill the entire screen
    SetSizer(mainSizer);

	styledTextCtrl = new wxStyledTextCtrl(this);

    // Turn on line numbers in the margin for margin #1
    styledTextCtrl->SetMarginType(1, wxSTC_MARGIN_NUMBER);
    styledTextCtrl->SetMarginWidth(1, 25);

    // Make the text area not show a horizontal scroll bar unless needed
    styledTextCtrl->SetScrollWidth(1);
    
    // Make the styledTextCtrl that takes up the entire screen
    mainSizer->Add(styledTextCtrl, 1, wxEXPAND);
}

void MainApp::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "Any file|*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = openFileDialog.GetPath();
    styledTextCtrl->LoadFile(path);
}

void MainApp::OnSaveAs(wxCommandEvent& event) {
	wxFileDialog saveFileDialog(this, _("Enter a filename"), "", "", "Any file|*", wxFD_SAVE|wxFD_FILE_MUST_EXIST);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString path = saveFileDialog.GetPath();
    styledTextCtrl->SaveFile(path);

    savePath = path;
}

void MainApp::OnSave(wxCommandEvent& event) {
    // Check if we haven't defined a save path yet
    if (savePath == "") {
        OnSaveAs(event);
    } else {
        styledTextCtrl->SaveFile(savePath);
    }
}

void MainApp::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainApp::OnUndo(wxCommandEvent& event) {
    styledTextCtrl->Undo();
}

void MainApp::OnRedo(wxCommandEvent& event) {
    styledTextCtrl->Redo();
}

void MainApp::OnCut(wxCommandEvent& event) {
    styledTextCtrl->Cut();
}

void MainApp::OnCopy(wxCommandEvent& event) {
    styledTextCtrl->Copy();
}

void MainApp::OnPaste(wxCommandEvent& event) {
    styledTextCtrl->Paste();
}

void MainApp::OnDelete(wxCommandEvent& event) {
    styledTextCtrl->Clear();
}

void MainApp::OnFind(wxCommandEvent& event) {
    findReplaceSizer->Show(true);
    replaceSizer->Show(false);

    // Update the layout
    Layout();
}

void MainApp::OnReplace(wxCommandEvent& event) {
    findReplaceSizer->Show(true);
    replaceSizer->Show(true);

    // Update the layout
    Layout();
}

void MainApp::OnCloseFindReplace(wxCommandEvent& event) {
    findReplaceSizer->Show(false);
    replaceSizer->Show(false);

    // Update the layout
    Layout();
}

void MainApp::OnSelectAll(wxCommandEvent& event) {
    styledTextCtrl->SelectAll();
}

void MainApp::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A simple text editor to learn about GUI applications in C++.", "About", wxOK | wxICON_INFORMATION);
}

void MainApp::OnNew(wxCommandEvent& event) {
    styledTextCtrl->Clear();
}