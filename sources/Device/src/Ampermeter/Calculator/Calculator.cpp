// 2022/10/19 08:16:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/Calculator/Calculator.h"
#include "Ampermeter/Calculator/FFT.h"
#include "Ampermeter/Calculator/PeriodInt.h"
#include "Ampermeter/Calculator/Averager.h"
#include <cmath>


namespace Calculator
{
    static int num_averages = 0;
    static Averager<double, 8> dc;
    static Averager<double, 8> ac;

    static BufferADC data;

    static double CalculateAC(int period, double *values);
    static double CalculateDC(int period);
}

SampleRate Calculator::AppendData(const BufferADC &_data)
{
    data = _data;

    int period = PeriodInt(data).ToPoints();

    double dc_val = CalculateDC(period);

    dc.Push(dc_val);

    double values[BufferADC::SIZE];

    for (int i = 0; i < period; i++)
    {
        values[i] = data[i].Real() - dc_val;
    }

    ac.Push(CalculateAC(period, values));

    FFT fft(data);

    return SampleRate::Current::Get();
}


double Calculator::GetAC()
{
    return ac.Get();
}


double Calculator::GetDC()
{
    return dc.Get();
}


void Calculator::SetAverages(int num_ave)
{
    num_averages = num_ave;
}


double Calculator::CalculateAC(int period, double *values)
{
    double sum = 0.0;

    for (int i = 0; i < period; i++)
    {
        sum += values[i] * values[i];
    }

    return std::sqrt(sum / period);
}


double Calculator::CalculateDC(int period)
{
    double sum = 0.0;

    for (int i = 0; i < period; i++)
    {
        sum += data[i].Real();
    }

    return sum / (double)period;
}
