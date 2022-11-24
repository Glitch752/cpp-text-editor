#include "main.h"
#include "icon.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    Icon *icon = new Icon(wxT("Text editor"));
    icon->Show(true);

    return true;
}