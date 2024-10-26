// 2023/11/09 12:21:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/AD7691.h"
#include <cstdlib>


SampleRate::E SampleRate::value = SampleRate::_10us;


uint SampleRate::TimeUSonPoint()
{
    static const uint times[Count] =
    {
        10,
        100,
        1000
    };

    return times[value];
}


float SampleRate::MinFrequency()
{
    static const float freq[Count] =
    {
        0.4f,
        4.0f,
        40.0f
    };

    return freq[value];
}


float SampleRate::MaxFrequency()
{
    static const float freq[Count] =
    {
        4.0f,
        40.0f,
        5e3f
    };

    return freq[value];
}


namespace AD7691
{
    static int counter = 0;
}


ValueADC::ValueADC(int reading)
{
    value = reading - cal.zero[Range::Current()].GetFull();
}


void AD7691::Init()
{

}


ValueADC AD7691::ReadValue()
{
    return ValueADC(ReadValueRAW());
}


static float GetSample(float freq, int num_sample)
{
    float T = 1.0f / freq;

    float samples_in_T = T / 10e-6f;

    float radians_in_T = 2.0f * M_PI;

    float radians_in_sample = radians_in_T / samples_in_T;

    return std::sinf(radians_in_sample * num_sample);
}


int AD7691::ReadValueRAW()
{
    float amplitude = 0.8f;

    float value = amplitude * GetSample(4900.95f, counter);

//    value += (float)std::rand() / (float)RAND_MAX / 2.0f;

    value *= 0x1FFFF;           // 17 ��� � �������� - ������������ ��������

    counter++;

    return (int)value;
}


int AD7691::GetAverageValue()
{
    return 0;
}
