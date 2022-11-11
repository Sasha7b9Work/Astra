// 2022/11/10 22:26:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "TextString.h"


class WindowMeasure
{
public:
    WindowMeasure(int x, int y, int font, pchar _title, const Color &back = Color::Count);
    void Enable();
    void Disable();
    void SetMeasure(char [TextString::MAX_LEN]);
    void OnChangeRangeEvent();
private:
    static const int HEIGHT = 92;
    static const int WIDTH = 600;
    static const int WIDTH_DIGIT = 40;
    static const int DELTA = 0;

    TextString title;
    TextString point;
    TextString digit1;
    TextString digit2;
    TextString digit3;
    TextString digit4;
    TextString digit5;

//    TextString sign;
//    TextString units;

    TextString *digits[5];

    Color colorBack;
};


class WindowMeasureAC : public WindowMeasure
{
public:
    WindowMeasureAC(int x, int y, int font) : WindowMeasure(x, y, font, "AC:") {}
private:
};


class WindowMeasureDC : public WindowMeasure
{
public:
    WindowMeasureDC(int x, int y, int font) : WindowMeasure(x, y, font, "DC:") {}
private:
};
