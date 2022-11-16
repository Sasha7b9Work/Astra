// 2022/11/01 12:57:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/Calibrator.h"
#include "Nextion/Nextion.h"
#include "Hardware/Timer.h"
#include "Menu/Pages/Pages.h"


namespace Calibrator
{
    static bool in_process = false;
}


void Calibrator::ExecuteCalibration()
{
    in_process = true;

    Nextion::Page::Enable(1);

    TimeMeterMS meter;

    while (meter.ElapsedTime() < 500)
    {

    }

    Nextion::Page::Enable(0);

    PageTwo::self->SetAsCurrent();
}


bool Calibrator::InProcess()
{
    return in_process;
}
