// 2022/10/28 22:55:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Screen.h"


Frame *Frame::self = nullptr;


Frame::Frame(const wxString &title)
    :wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    self = this;

    new Screen(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(Screen::self);
    SetSizer(sizer);

    SetSizeAndPosition();
}


void Frame::SetSizeAndPosition()
{
    SetClientSize(Screen::WIDTH, Screen::HEIGHT);

    wxTopLevelWindowBase::SetMinSize(GetSize());
    wxTopLevelWindowBase::SetMaxSize(GetSize());

    const int maxWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    const int maxHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    int x = (maxWidth - GetSize().x) / 2;
    int y = (maxHeight - GetSize().y) / 2;

    SetPosition({ x, y });
}
