// 2022/10/28 22:52:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#define WIN32_LEAN_AND_MEAN
#include "defines.h"
#include "Application.h"
#include "Screen.h"


void Application::Init()
{
    Screen::self->Init();
}


void Application::Update()
{
}
