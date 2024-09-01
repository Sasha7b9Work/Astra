// 2022/10/28 22:56:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "GUI/Application.h"
#include "GUI/MainWindow.h"


wxIMPLEMENT_APP(Application);


Application *Application::self = nullptr;


bool Application::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // create and show the main application window
    new MainWindow(_("A101 GUI version"));
    MainWindow::self->Show();

    Init();

    self = this;

    return true;
}
