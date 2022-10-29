// 2022/10/28 23:17:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Screen.h"
#include "Display/Painter.h"
#include "Display/DInterface.h"
#include <string>
#include <map>
#include <algorithm>


wxBitmap Screen::bitmap(Screen::WIDTH, Screen::HEIGHT);


Screen *Screen::self = nullptr;

static const int width_button = 130;
static const int height_button = 72;
static const int y_button = 405;


struct ButtonGUI
{
    ButtonGUI(int _index, int _x, int _y, int _width, int _height)
        : index(_index), text(""), x(_x), y(_y), width(_width), height(_height), enabled(true), highlight(false) {}

    void Draw();

    // ���������� true, ���� ������� ������ ������
    bool PixelInside(int x, int y);

    // "������" ������
    void Press();

    void SetText(pchar);

    void Enable();

    void Disable();

    void SetHightlight(bool);

private:
    int index;
    std::string text;
    int x;
    int y;
    int width;
    int height;
    bool enabled;
    bool highlight;
};


struct Font
{
    static wxFont Get(int num_font);
};


static ButtonGUI btn0(0, 3,   y_button, width_button, height_button);
static ButtonGUI btn1(1, 136, y_button, width_button, height_button);
static ButtonGUI btn2(2, 269, y_button, width_button, height_button);
static ButtonGUI btn3(3, 402, y_button, width_button, height_button);
static ButtonGUI btn4(4, 535, y_button, width_button, height_button);
static ButtonGUI btn5(5, 668, y_button, width_button, height_button);
static ButtonGUI btMenu(6, 725, 7, 67, 67);


static std::map<std::string, ButtonGUI *> buttons
{
    {"button0", &btn0},
    {"button1", &btn1},
    {"button2", &btn2},
    {"button3", &btn3},
    {"button4", &btn4},
    {"button5", &btn5},
    {"btMenu", &btMenu}
};


Screen::Screen(wxWindow *parent) : wxPanel(parent)
{
    self = this;

    SetMinSize({ Screen::WIDTH, Screen::HEIGHT });
    SetDoubleBuffered(true);
    Bind(wxEVT_PAINT, &Screen::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &Screen::OnMouseDown, this);
}


void Screen::OnPaint(wxPaintEvent &)
{
    wxPaintDC dc(this);

    dc.DrawBitmap(bitmap, 0, 0);
}


void Screen::OnMouseDown(wxMouseEvent &event)
{
    int x = event.GetX();
    int y = event.GetY();

    for (auto &elem : buttons)
    {
        ButtonGUI *button = elem.second;

        if (button->PixelInside(x, y))
        {
            button->Press();
        }
    }
}


void Screen::Init()
{
    Rect(WIDTH, HEIGHT).Fill(0, 0, Color::Background);

    for (auto &elem : buttons)
    {
        elem.second->Draw();
    }
}


void Screen::FillRectangle(int x, int y, int width, int height, const wxColor &color)
{
    wxMemoryDC dc;
    dc.SelectObject(bitmap);
    dc.SetBrush(color);
    dc.SetPen(color);
    dc.DrawRectangle({ x, y, width, height });
    dc.SelectObject(wxNullBitmap);
    Refresh();
}


void Screen::DrawLine(int x1, int y1, int x2, int y2, const wxColor &color)
{
    wxMemoryDC dc;
    dc.SelectObject(bitmap);
    dc.SetPen(color);
    dc.DrawLine(x1, y1, x2, y2);
    dc.SelectObject(wxNullBitmap);
    Refresh();
}


void Screen::DrawString(int x, int y, int num_font, const wxColor &color, pchar text)
{
    wxMemoryDC dc;
    dc.SelectObject(bitmap);
    dc.SetTextForeground(color);
    dc.SetFont(Font::Get(num_font));
    dc.DrawText(text, x, y);
    dc.SelectObject(wxNullBitmap);
    Refresh();
}


void Screen::Button::SetText(pchar name_button, pchar text)
{
    buttons[name_button]->SetText(text);
}


void Screen::Button::Highlight(pchar name_button, bool hightlight)
{
    buttons[name_button]->SetHightlight(hightlight);
}


void ButtonGUI::Draw()
{
    if (!enabled)
    {
        Rect(width, height).Fill(x, y, Color::Background);
    }
    else
    {
        Rect(width, height).Draw(x, y, Color::White);

        Color color_fill = highlight ? Color::ButtonPress : Color::Background;

        Rect(width - 2, height - 2).Fill(x + 1, y + 1, color_fill);

        int d = 20;
        Painter::DrawString(x + d, y + d, width - 2 * d, height - 2 * d, 3, Color::White, color_fill, text.c_str());
    }
}


void ButtonGUI::SetText(pchar _text)
{
    text = _text;
    Draw();
}


bool ButtonGUI::PixelInside(int pixel_x, int pixel_y)
{
    if (pixel_x < x)          { return false; }
    if (pixel_x > x + width)  { return false; }
    if (pixel_y < y)          { return false; }
    if (pixel_y > y + height) { return false; }

    return true;
}


void ButtonGUI::Press()
{
    DInterface::CallbackOnReceive((uint8)(0x30 + index));
    DInterface::CallbackOnReceive('Z');
}


void ButtonGUI::Enable()
{
    enabled = true;

    Draw();
}


void ButtonGUI::Disable()
{
    enabled = false;

    Draw();
}


void ButtonGUI::SetHightlight(bool _highlight)
{
    highlight = _highlight;

    Draw();
}


void Screen::Button::Enable(pchar name_button)
{
    buttons[name_button]->Enable();
}


void Screen::Button::Disable(pchar name_button)
{
    buttons[name_button]->Disable();
}


wxFont Font::Get(int num_font)
{
    static const int sizes[10] = { 30, 30, 30, 20, 30, 30, 30, 60, 30, 30 };

    return wxFont(sizes[num_font], wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL);
}
