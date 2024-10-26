// 2022/10/19 08:16:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Ampermeter/BufferADC.h"
#include "Ampermeter/Ampermeter.h"


namespace Calculator
{
    // ������� ���������� ������� ������������� ��� ���������� ����� ������
    SampleRate AppendData();

    void Reset();

    REAL GetAbsAC(bool *correct);
    Measure GetMeasureAC();
    REAL GetAbsDC(bool *correct);
    Measure GetMeasureDC();
    REAL GetValueMin(bool *correct);
    Measure GetMeasureMin();
    REAL GetValueMax(bool *correct);
    Measure GetMeasureMax();
    Measure GetMeasureAmpl();
    Measure GetMeasureFrequency();
    Measure GetMeasurePeak();
}
