// 2022/11/10 22:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Controls/WindowsMeasures.h"
#include "Ampermeter/InputRelays.h"
#include "Nextion/Nextion.h"
#include "Menu/Pages/Pages.h"
#include "Ampermeter/Ampermeter.h"
#include <cstring>
#include <cstdio>
#include <cmath>


void WindowMeasure::Reset()
{
    int range = Range::Current();

    if (range == 0 || range == 3)
    {
        cntrlDigits.SetLabel("*.****");
    }
    else if (range == 1 || range == 4 || range == 5)
    {
        cntrlDigits.SetLabel("**.***");
    }
    else if (range == 2)
    {
        cntrlDigits.SetLabel("***.**");
    }

    cntrlUnits.SetLabel(range < 3 ? "mA" : "A");

    cntrlSign.SetLabel("");

    if (label_type[0] != '\0')
    {
        cntrlType.SetLabel(label_type);
    }

    buf_measure[0] = '\0';
}


void WindowMeasure::SetMeasure(float value)
{
    if (Page::Current() != PageMain::self)
    {
        return;
    }

    char buffer[30];

    buffer[0] = (value >= 0.0f) ? '+' : '-';

    std::sprintf(buffer + 1, "%5f", (double)value);

    SetMeasure(buffer);
}


void WindowMeasure::SetMeasure(pchar measure)
{
    if (measure[0])
    {
        if (cntrlSign.IsExist())
        {
            char sign[2] = { measure[0], '\0' };
            cntrlSign.SetLabel(sign);
        }

        char buffer[7];

        std::memcpy(buffer, measure + 1, 6);
        buffer[6] = '\0';

        cntrlDigits.SetLabel(buffer);

        if (measure[std::strlen(measure) - 2] == ' ')
        {
            cntrlUnits.SetLabel("A");
        }
        else
        {
            cntrlUnits.SetLabel("mA");
        }
    }
}


void WindowMeasure::Flash()
{
    cntrlDigits.Flash();
}


void WindowMeasure::Draw(const Measure &measure, int range)
{
    if (!measure.correct)
    {
        Reset();
    }
    else
    {
        if (measure.out_of_range)
        {
            for (int i = 0; (i < TextString::MAX_LEN) && (buf_measure[i] != '\0'); i++)
            {
                if (buf_measure[i] != '.') { buf_measure[i] = '8'; }
            }
        }
        else
        {
            static const int after[6] = { 4, 3, 2, 4, 3, 3 };
            const pchar suffix = (range < 3) ? "mA" : "A";

            ConvertDoubleToText(measure.value, buf_measure, after[range], suffix);
        }

        SetMeasure(buf_measure);
    }
}


void WindowMeasure::ConvertDoubleToText(float value, char out[TextString::MAX_LEN], int after, pchar suffix)
{
    std::strcpy(out, value < 0.0f ? "-" : "+");

    value = std::fabs(value);

    int before = 5 - after;

    if (before == 3)
    {
        if (value < 10.0f)
        {
            std::strcat(out, "00");
        }
        else if (value < 100.0f)
        {
            std::strcat(out, "0");
        }
    }

    if (before == 2 && value < 10.0f)
    {
        std::strcat(out, "0");
    }

    // Отбрасываем цифры, которых нет на экране - во избежание бага, когда 10 превращеется в 1 (при 9.999999)
    {
        for (int i = 0; i < after; i++)
        {
            value *= 10.0f;
        }

        value = (float)((int)value);

        for (int i = 0; i < after; i++)
        {
            value /= 10.0f;
        }
    }

    char buffer[TextString::MAX_LEN];

    char format[] = { '%', '0', (char)((before + 1) | 0x30), '.', (char)(after | 0x30), 'f', ' ', '%', 's', '\0' };

    std::sprintf(buffer, format, (double)value, suffix);

    std::strcat(out, buffer);
}

