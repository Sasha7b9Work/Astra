// 2022/10/18 16:18:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Measurer/BufferADC.h"
#include "Display/DInterface.h"
#include <limits>


void BufferADC::ConvertToVoltage()
{
    min = std::numeric_limits<float>::max();
    max = std::numeric_limits<float>::min();

    min_raw = (uint)(-1);
    max_raw = 0;

    for (int i = 0; i < SIZE; i++)
    {
        uint raw_value = raw[i];

        if (raw_value < min_raw)
        {
            min_raw = raw_value;
        }
        if (raw_value > max_raw)
        {
            max_raw = raw_value;
        }

        float value = (float)raw_value;

        if (raw_value > (1 << 17))
        {
            value -= (float)(1 << 18);
        }

        const float k = 5.0f / (1 << 17);

        volt[i] = (float)value * k;

        if (volt[i] < min)
        {
            min = volt[i];
        }

        if (volt[i] > max)
        {
            max = volt[i];
        }
    }

    DInterface::SendCommandFormat("textDELTA.txt=\"%d\"", max_raw - min_raw);
}

