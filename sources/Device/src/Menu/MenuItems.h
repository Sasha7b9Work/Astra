// 2022/10/24 11:25:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Log.h"


struct Button
{
public:

    // _highlight - � ���� ��������� ������ ��������� ��� ������ ��������� �� ������
    Button(bool _highlight, void (*_funcOnPress)(Button *), void (*_funcOnInit)(Button *) = EmptyFuncInit) :
        highlight(_highlight), funcOnPress(_funcOnPress), funcOnInit(_funcOnInit)
    {
    }

    void Init() { funcOnInit(this); }

    void Press();

    void ToggleHighlight();

    // ���������� true, ���� ������ ��������� � ���������� ���������
    bool IsHightlight() const { return highlight; }

private:

    bool highlight;
    void (*funcOnPress)(Button *);
    void (*funcOnInit)(Button *);

    static void EmptyFuncInit(Button *) {}
};


struct Page
{
    Page(Button *btn0, Button *btn1, Button *btn2, Button *btn3, Button *btn4, Button *btn5);

    static Page *Current() { return current; }

    void SetAsCurrent();

    // ���������� ������ �� 0 �� 5
    Button *GetButton(int index);

    void SetButton(int index, Button *);

private:

    Button *buttons[20];

    static Page *current;
};
