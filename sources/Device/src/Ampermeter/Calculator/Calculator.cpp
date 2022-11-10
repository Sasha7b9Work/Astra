// 2022/10/19 08:16:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/Calculator/Calculator.h"
#include "Ampermeter/Calculator/ResolverFFT.h"
#include "Ampermeter/Calculator/ResolverPeriodFFT.h"
#include "Ampermeter/Calculator/ResolverPeriodSamples.h"
#include "Ampermeter/Calculator/Averager.h"
#include "Ampermeter/Calculator/ResolverDC.h"
#include "Ampermeter/Calculator/ResolverAC.h"
#include "Hardware/Timer.h"
#include <cmath>


namespace Calculator
{
    static int num_averages = 0;
    static Averager<double, 1> dc;
    static Averager<double, 1> ac;

    static double k = 1.0;
}


void Calculator::Reset(int range)
{
    dc.Reset();
    ac.Reset();

    static const double koeff[6] = { 1e-2, 1e-1, 1e0, 1e-2, 1e-1, 1e0 };

    k = koeff[range] * 61.81;
}


SampleRate Calculator::AppendData(const BufferADC &data)
{
    Period period = ResolverPeriodSamples(data).GetResult();

    ac.Push(ResolverAC(data, period).GetResult() * k);

    return SampleRate::Current::Get();
}


//SampleRate Calculator::AppendData(const BufferADC &data)
//{
//    double dc_val = ResolverDC::Calculate(data, period);
//
//    dc.Push(dc_val * k);
//}


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
