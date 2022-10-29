// 2022/10/29 09:37:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Painter.h"
#include "Screen.h"


void Rectangle::Fill(int x, int y, const Color &color)
{
    Screen::self->DrawRectangle(x, y, width, height, wxColor(color.ToRaw()));
}


void Painter::DrawWave(uint8 *, int)
{

}


void Painter::DrawString(int x, int y, int width, int height, int font, const Color &color, const Color &back_color, pchar)
{

}



void Painter::SetTextButton(pchar name_button, pchar text)
{

}


void Painter::SetValButton(pchar name_button, int val)
{

}
