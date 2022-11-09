// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Editor/Editor.h"
#include "Editor/Form.h"
#include "Editor/Painter/Canvas.h"
#include "Editor/History.h"


void init()
{
    Frame *frame = new Frame("�������� �������� �6-49");

    TheCanvas = new Canvas(frame);

    TheForm = new Form();

	History::Add(TheForm);
}

void update()
{
    TheCanvas->Draw();
}