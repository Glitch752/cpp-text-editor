#include "./icon.h"
#include <wx/wx.h>

Icon::Icon(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) {
    wxImage::AddHandler(new wxXPMHandler);

    wxIcon icon(wxT("./tempIcon.xpm"), wxBITMAP_TYPE_XPM);
    SetIcon(icon);

    Center();
}