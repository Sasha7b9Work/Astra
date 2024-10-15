// 2022/10/18 15:54:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Ampermeter/Ampermeter.h"
#include "Ampermeter/BufferADC.h"
#include "Hardware/HAL/HAL.h"
#include "Ampermeter/AD7691.h"
#include "Ampermeter/Calculator/Calculator.h"
#include "Nextion/Display.h"
#include "Hardware/HAL/HAL.h"
#include "Menu/MenuItems.h"
#include "Ampermeter/InputRelays.h"
#include "Hardware/Timer.h"
#include "Nextion/DiagramInput.h"
#include "Ampermeter/Calculator/Averager.h"
#include "Settings/Settings.h"
#include "Ampermeter/FIR.h"
#include "stm_includes.h"
#include "Menu/Pages/Pages.h"
#include "Nextion/Nextion.h"
#include "Utils/String.h"
#include "Hardware/HAL/HAL_PIO.h"
#include <cmath>
#include <cstdio>


namespace Ampermeter
{
    namespace AVP
    {
        static bool is_enabled = false;

        void Enable()
        {
            ZeroAC::Disable();
            ZeroDC::Disable();

            is_enabled = true;

            PageMain::btnAVP.SetToggled(true, false);
        }

        void Disable()
        {
            is_enabled = false;
        }
    }

    // ��������� ������ �� ���
    struct MiddlerOf3
    {
        void Push(ValueADC value)
        {
            averager.Push(value);
        }
        ValueADC Get()
        {
            if (averager.NumElements() > 2)
            {
                return ValueADC::FromRaw(middle_of_3(averager.Pop(0), averager.Pop(1), averager.Pop(2)));
            }
            else if (averager.NumElements() == 2)
            {
                return averager.Pop(1);
            }

            return averager.Pop(0);
        }

    private:

        Averager <ValueADC, 3> averager;

        int middle_of_3(int a, int b, int c)
        {
            if ((a <= b) && (a <= c))
            {
                return (b <= c) ? b : c;
            }
            else if ((b <= a) && (b <= c))
            {
                return (a <= c) ? a : c;
            }
            return (a <= b) ? a : b;
        }
    };

    // ��������� �������� ������� �� ������� ���������
    static bool OutOfRange();

    // ���������� �������� ������� ��������� - ����� ������� �� ���������� ��������
    static bool VerySmall();

    // ��������� ����
    static void AdjustmentZero();
}


void Ampermeter::Init()
{
    HAL_TIM4::Init();

    AD7691::Init();
}


void Ampermeter::Update()
{
    if (Page::Current() != PageMain::self && Page::Current() != PageGraph::self && Page::Current() != PageCalibration::self)
    {
        return;
    }

    if (Page::Current() == PageGraph::self &&   // ���� �������� ��������� ��������
        DiagramInput::DataInstalled())          // � ������ ��� ��������� ������� � �������
    {
        return;                                 // ����������� �� �����, ������ ��� ��� �������� ����� �������
    }

    AdjustmentZero();

    MeasurementCycle();

    SampleRate::Current::Set(Calculator::AppendData());

    if (OutOfRange())
    {
    }
    else
    {
//        DiagramInput::_InstallData();
    }

    if (AVP::is_enabled)
    {
        int range = Range::Current();

        int min = 4;
        int max = 5;

        if (range < 4)
        {
            min = 0;
            max = 3;
        }

        if (OutOfRange())
        {
            if (range < max)
            {
                PageMain::SetRange(max);
            }
        }
        else if (VerySmall())
        {
            if (range > min)
            {
                PageMain::SetRange(range - 1);
            }
        }

        AVP::Enable();  // ����� ������ ��������, ������ ��� ������� �� ������ ��������� ���
    }
}


Measure Ampermeter::GetDC()
{
    bool correct = false;

    REAL dc = Calculator::GetAbsDC(&correct);

    REAL zero = ZeroDC::LevelAbsFull();

    if (Range::Current() > 2)
    {
        zero /= 1e3;
    }

    return Measure(dc - zero, OutOfRange(), correct);

//    REAL result = 1.0f;
//
//    result -= 1e-4f;
//
//    result += 1e-6f * TIME_MS / 1000;
//
//    return Measure(result, false, true);
}


Measure Ampermeter::GetAC()
{
    bool correct = false;

    REAL ac = Calculator::GetAbsAC(&correct);

    REAL zero = ZeroAC::LevelAbs();

    if (Range::Current() > 2)
    {
        zero /= 1e3;
    }

    return Measure(ac - zero, OutOfRange(), correct);
}


Measure Ampermeter::GetMin()
{
    bool correct = false;

    REAL min = Calculator::GetValueMin(&correct);

    REAL zero = ZeroDC::LevelAbsFull();

    if (Range::Current() > 2)
    {
        zero /= 1e3;
    }

    return Measure(min - zero, OutOfRange(), correct);
}


Measure Ampermeter::GetMax()
{
    bool correct = false;

    REAL max = Calculator::GetValueMax(&correct);

    REAL zero = ZeroDC::LevelAbsFull();

    if (Range::Current() > 2)
    {
        zero /= 1e3;
    }

    return Measure(max - zero, OutOfRange(), correct);
}


Measure Ampermeter::GetFrequency()
{
    bool correct = false;

    REAL frequency = Calculator::GetValueFrequency(&correct);

    return Measure(Measure::LimitFrequency(frequency), OutOfRange(), correct);
}


Measure Ampermeter::GetPeak()
{
    bool correct = false;

    REAL max = Calculator::GetValueMax(&correct);

    REAL min = Calculator::GetValueMin(&correct);

    return Measure(max - min, OutOfRange(), correct);
}


Measure Ampermeter::GetAmpl()
{
    bool correct = false;

    REAL ampl = Calculator::GetValueAmpl(&correct);

    if (Range::Current() > 2)
    {
        ampl /= 1e3;
    }

    return Measure(ampl, OutOfRange(), correct);
}


void Ampermeter::MeasurementCycle()
{
    AD7691::ResetValue();

    TimeMeterMS meter;

    BufferADC::Clear(SampleRate::Current::Get());

    uint period = SampleRate::Current::Get().TimeUS();

    HAL_TIM4::StartPeriodicUS(period * 2);

    int num_sample = 0;

    int64 sum = 0;
    int counter = 0;

    while (!BufferADC::IsFull())
    {
#ifndef WIN32
        while (TIM4->CNT < period)
        {
        }

        TIM4->CNT = 0;
#endif

        ValueADC value = AD7691::ReadValue();

        sum += value._raw;
        counter++;

        if (set.firLPF)
        {
            value = ValueADC::FromRaw(FIR::Step(value.Raw()));

            if (num_sample++ > 200)
            {
                BufferADC::Push(value);
            }
        }
        else
        {
            BufferADC::Push(value);
            num_sample++;
        }
    }

    HAL_TIM4::Stop();

    if (set.middle_of_3)
    {
        BufferADC::MiddleOf3();
    }

    if (set.smooth)
    {
        BufferADC::SmoothOut();
    }

    BufferADC::CalculateLimits((int)sum / counter);
}


bool Ampermeter::OutOfRange()
{
    static const REAL maxs[6] = { 2.0, 2e1, 2e2, 2e3, 2e4, 5e4 };

    REAL max = maxs[Range::Current()] * 1.15;

    bool correct_dc = false;
    bool correct_ac = false;

    REAL dc = Calculator::GetAbsDC(&correct_dc);
    REAL ac = Calculator::GetAbsAC(&correct_ac);

    REAL value = std::fabs(dc) + ac;

    if (value > max)
    {
        LOG_WRITE("out range dc = %f, ac = %f", (double)dc, (double)ac);

        return true;
    }

    return false;
}


bool Ampermeter::VerySmall()
{
    static const REAL mins[6] = { 0.0, 2e0, 2e1, 2e2, 2e3, 20e3 };

    REAL min = mins[Range::Current()];

    bool correct_dc = false;
    bool correct_ac = false;

    REAL dc = Calculator::GetAbsDC(&correct_dc);
    REAL ac = Calculator::GetAbsAC(&correct_ac);

    if (!correct_ac || !correct_dc)
    {
        return false;
    }

    REAL value = std::fabs(dc) + ac;

    return value <= min;
}


void Ampermeter::OnEventChangeRange()
{
    Calculator::Reset();
}


void Ampermeter::AdjustmentZero()
{
    static int prev_range = -1;

    static uint next_time = 0;

    static bool need_pause = true;

    if (Range::Current() == prev_range)
    {
        need_pause = true;

        if (TIME_MS < next_time)
        {
            return;
        }
    }
    else
    {
        if (need_pause)
        {
            need_pause = false;

            if (Range::Current() > 3)
            {
                Timer::Delay(400);
            }
        }
    }

    next_time = TIME_MS + 10000;

    prev_range = Range::Current();

    CalibrationSettings::Zero &zero = cal.zero[Range::Current()];
    const int const_val = zero.GetConst();

    zero.SetConst(0);
    zero.SetVar(0);

//    int non_zero_var = AD7691::_GetAverageValue();

    InputRelays::EnableZero(false);

    int zero_var = AD7691::GetAverageValue();

    zero.SetVar(zero_var);

    InputRelays::DisableZero(false);

    zero.SetConst(const_val);

//    static int counter = 0;

//    Nextion::DrawString(160, 60, 440, 40, 0, Color::White, Color::Background, String<>("%d nz_v=%d v=%d c=%d", counter++, non_zero_var, zero_var, const_val).c_str());

    HAL_PIO::Write(PIN_ZERO, false);
}


REAL Measure::LimitFrequency(REAL value)
{
    if (value < 1e-3)
    {
        return 1e-3;
    }

    if (value > 1e6)
    {
        return 1e6;
    }

    return value;
}
