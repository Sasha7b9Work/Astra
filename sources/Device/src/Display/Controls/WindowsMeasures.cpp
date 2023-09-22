// 2022/11/10 22:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Controls/WindowsMeasures.h"
#include "Ampermeter/InputRelays.h"
#include "Nextion/Nextion.h"


void WindowMeasure::Clear()
{
    Nextion::Text::SetText(cntrlType, "");
    Nextion::Text::SetText(cntrlSign, "");
    Nextion::Text::SetText(cntrlDigits, "");
    Nextion::Text::SetText(cntrlUnits, "");
}

void WindowMeasure::SetMeasure(pchar)
{

}
