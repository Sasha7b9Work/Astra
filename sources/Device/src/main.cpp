// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "Nextion/Nextion.h"
#include "Hardware/HAL/HAL.h"
#include "Ampermeter/Ampermeter.h"
#include "Menu/Menu.h"
#include "Utils/Profiler.h"
#include "Generator/Generator.h"
#include "Hardware/Timer.h"


int main()
{
    HAL::Init();

    HAL_TIM::Delay(500);

    Ampermeter::Init();

    Menu::Init();

    Display::Init();

    Generator::SetPicAC(1);

    Generator::SetFrequency(1e3f);

    Generator::Enable();

    static TimeMeterMS meter;

    while (1)
    {
        Ampermeter::Update();

        Display::Update();

        Nextion::Update();

        Profiler::Update();

        LOG_WRITE("time cycle %d", meter.ElapsedTime());
        meter.Reset();
    }
}
