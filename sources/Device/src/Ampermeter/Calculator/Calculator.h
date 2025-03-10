// 2022/10/19 08:16:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Ampermeter/BufferADC.h"
#include "Ampermeter/Ampermeter.h"
#include "Ampermeter/Calculator/ResolverPeriodSamples.h"


namespace Calculator
{
    // ������� ���������� ������� ������������� ��� ���������� ����� ������
    void AppendData();

    void Reset();

    Period GetPeriod();

    // ����������� �������� ���������� ������������
    REAL GetAbsAC(bool *correct);
    Measure GetMeasureAC();

    // ����������� �������� ������� ����
    REAL GetAbsDC(bool *correct);
    Measure GetMeasureDC();

    // ����������� �������������� �������� ����
    REAL GetValueMinSteady(bool *correct);
    Measure GetMeasureMinSteady();

    // ������������ �������������� �������� ����
    REAL GetValueMaxSteady(bool *correct);
    Measure GetMeasureMaxSteady();

    // ������� ����� ���� � ���
    Measure GetMeasureAmplSteady();

    // ������� ����� �������� ���������� - ����������� ��� � ����
    Measure GetMeasurePeak();

    Measure GetMeasureFrequency();

    // ��������� �������� ������� �� ������� ���������
    bool OutOfRange();
}
