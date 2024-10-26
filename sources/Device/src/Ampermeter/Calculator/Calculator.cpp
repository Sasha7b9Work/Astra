// 2022/10/19 08:16:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/Calculator/Calculator.h"
#include "Ampermeter/Calculator/ResolverPeriodSamples.h"
#include "Ampermeter/Calculator/Averager.h"
#include "Ampermeter/Calculator/ResolverAC.h"
#include "Ampermeter/Calculator/Resolvers.h"
#include "Hardware/Timer.h"
#include "Ampermeter/InputRelays.h"
#include "Settings/Settings.h"
#include "Nextion/Display.h"
#include <cmath>


#define GET_RELATIVE(arr)                           \
    *correct = arr.NumElements() > 0;               \
    REAL relative = (*correct) ? arr.Get() : 0.0


namespace Calculator
{
#define NUM_AVERAGES 1

    // ��������, ���������� � ������� - mA ��� 2,20,200��, ������ ��� 2A, 20A, 50A
    static AveragerReal<NUM_AVERAGES> dc;
    static AveragerReal<NUM_AVERAGES> ac;
    static AveragerReal<NUM_AVERAGES> min;
    static AveragerReal<NUM_AVERAGES> max;
    static AveragerReal<NUM_AVERAGES> ampl;
    static AveragerReal<NUM_AVERAGES> frequency;
}


void Calculator::Reset()
{
    dc.Reset();
    ac.Reset();
    min.Reset();
    max.Reset();
    ampl.Reset();
    frequency.Reset();
}


SampleRate Calculator::AppendData()
{
    Period period = ResolverPeriodSamples().GetResult();

    const REAL k = cal.gain[Range::Current()].Get();

    // ������� AC
    {
        REAL value_ac = ResolverAC(period).GetResult();

        ac.Push(value_ac * k);
    }

    // ������� ��
    {
        REAL value_dc = -period.dc.Real();

        dc.Push(value_dc * k);
    }

    // ������� MIN � MAX � AMPL
    {
        ResolverMinMax resolver_min_max(period);

        min.Push(resolver_min_max.GetMin() * k);

        max.Push(resolver_min_max.GetMax() * k);

        ResolverAmpl resolver_ampl(period, resolver_min_max.GetMin(), resolver_min_max.GetMax());

        REAL ampl_value = resolver_ampl.GetResult();

        ampl.Push(ampl_value * k);
    }

#if 0

    if (ampl.Get() > Range::Max(Range::Current()) * 0.1)        // ������� ������� ������ ���� ��������� ��������� 10% �� ������������� ��������
    {
        frequency.Push(ResolverFrequency(period).GetFrequency());
    }
    else
    {
        frequency.Reset();
    }

#else

    REAL freq = ResolverFrequency(period).GetFrequency();

    if (freq <= 5e3)
    {
        frequency.Push(ResolverFrequency(period).GetFrequency());
    }
    else
    {
        frequency.Reset();
    }

#endif

    return SampleRate::Current::Get();
}


REAL Calculator::GetValueFrequency(bool *correct)
{
    *correct = (frequency.NumElements() > 0);

    return frequency.NumElements() ? frequency.Get() : 0.0;
}


REAL Calculator::GetAbsAC(bool *correct)
{
    GET_RELATIVE(ac);

    return relative * (Range::Current() > 2 ? 1e3 : 1.0);
}


REAL Calculator::GetAbsDC(bool *correct)
{
    GET_RELATIVE(dc);

    return relative * (Range::Current() > 2 ? 1e3 : 1.0);
}


REAL Calculator::GetValueMin(bool *correct)
{
    GET_RELATIVE(min);

    return relative * (Range::Current() > 2 ? 1e3 : 1.0);
}


REAL Calculator::GetValueMax(bool *correct)
{
    GET_RELATIVE(max);

    return relative * (Range::Current() > 2 ? 1e3 : 1.0);
}


REAL Calculator::GetValueAmpl(bool *correct)
{
    GET_RELATIVE(ampl);

    return relative * (Range::Current() > 2 ? 1e3 : 1.0);
}
