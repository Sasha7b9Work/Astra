// 2022/10/24 12:16:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/PageTwo.h"
#include "Display/DiagramInput.h"


namespace PageTwo
{
    static void ApplyActionButtonInput(Button *, int action)
    {
        DiagramInput::Enable(action == 1);
    }

    static Button buttonInput("button0", "Input", false, ApplyActionButtonInput);


    static void ApplyActionButtonFFT(Button *, int)
    {

    }

    static Button buttonFFT("button1", "FFT", false, ApplyActionButtonFFT);


    static void ApplyActionButtonZero(Button *, int)
    {

    }

    static Button buttonZero("button2", "Zero", false, ApplyActionButtonZero);


    static void ApplyActionButtonDebug(Button *, int)
    {

    }

    static Button buttonDebug("button3", "Debug", false, ApplyActionButtonDebug);


    static void ApplyActionButton4(Button *, int)
    {

    }

    static Button button4("button4", "", false, ApplyActionButton4);


    static void ApplyActionButton5(Button *, int)
    {

    }

    static Button button5("button5", "", false, ApplyActionButton5);


    Button *btnInput = &buttonInput;
    Button *btnFFT = &buttonFFT;
    Button *btnZero = &buttonZero;

    static Page pageTwo(&buttonInput, &buttonFFT, &buttonZero, &buttonDebug, &button4, &button5);

    Page *self = &pageTwo;
}
