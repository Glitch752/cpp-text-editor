#include "main.h"
#include "mainapp.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    MainApp *app = new MainApp(wxT("Text editor"));
    app->Show(true);

    return true;
}