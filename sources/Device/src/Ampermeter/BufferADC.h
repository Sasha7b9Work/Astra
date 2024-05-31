// 2022/10/18 16:18:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Ampermeter/AD7691.h"


namespace BufferADC
{
    static const int SIZE = 16 * 1024;

    void _Push(ValueADC word);

    int NumElements();

    bool IsFull();

    void Clear(SampleRate);

    void CalculateLimits(int ave);

    ValueADC Min();

    ValueADC Max();

    void LogUART();

    SampleRate GetSampleRate();

    ValueADC At(int i);

    // �������� ��������� ������ �� ���
    void MiddleOf3();

    // �������� ������
    void SmoothOut();
}
