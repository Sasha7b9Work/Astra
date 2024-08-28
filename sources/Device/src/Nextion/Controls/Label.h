// 2022/11/10 19:59:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Nextion/Colors.h"
#include "Settings/Settings.h"


/*
*   ��������� ����� �� ����������� ��������
*/


struct Label
{
    static const int MAX_LEN = 32;

    Label(int _x, int _y, int _w, int _h, int _font, pchar _textRU, pchar _textEN, const Color &_colorText,
        bool _h_aligned = false, const Color &_colorBack = Color::Count);
    void Hide();
    void Show();
    void SetVisible(bool);
    void SetText(const char _textRU[MAX_LEN], const char _textEN[MAX_LEN]);
    void SetX(int _x) { x = _x; }
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetWidth() const { return width; }
    pchar Text() const;
private:
    char  text[Lang::Count][MAX_LEN];
    int   x;
    int   y;
    int   width;
    int   height;
    int   font;
    bool  h_aligned;
    Color colorText;
    Color colorBack;
};
