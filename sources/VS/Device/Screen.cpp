// 2022/10/28 23:17:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Screen.h"


wxBitmap Screen::bitmap(Screen::WIDTH, Screen::HEIGHT);


Screen *Screen::self = nullptr;


Screen::Screen(wxWindow *parent) : wxPanel(parent)
{
    self = this;

    SetMinSize({ Screen::WIDTH, Screen::HEIGHT });
    SetDoubleBuffered(true);
    Bind(wxEVT_PAINT, &Screen::OnPaint, this);
}


void Screen::OnPaint(wxPaintEvent &)
{
    wxPaintDC dc(this);

    dc.DrawBitmap(bitmap, 0, 0);
}


void Screen::DrawRectangle(int x, int y, int width, int height, const wxColor &color)
{
    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);
    wxBrush brush(color, wxTRANSPARENT);
    memDC.SetBrush(brush);
    memDC.DrawRectangle({ x, y, width, height });
    memDC.SelectObject(wxNullBitmap);
    Refresh();
}
