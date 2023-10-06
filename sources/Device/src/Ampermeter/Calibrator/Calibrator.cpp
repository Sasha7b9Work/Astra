// 2022/11/01 12:57:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Nextion/Nextion.h"
#include "Hardware/Timer.h"
#include "Menu/Pages/Pages.h"
#include "Hardware/HAL/HAL.h"
#include "Settings/Settings.h"
#include "Ampermeter/Ampermeter.h"
#include "Ampermeter/Calculator/Calculator.h"
#include "Ampermeter/InputRelays.h"
#include "Utils/Math.h"
#include "Ampermeter/Calibrator/Calibrator.h"
#include <cstdio>
#include <cmath>


namespace Calibrator
{
    struct CalibratorZero
    {
        CalibratorZero(int _range) : range(_range) {}
        void Run();
    private:
        int range;
        float CalculateDC(int zero);
    };

    static void (*callbackUpdate)() = nullptr;

    // ������������� ��������
    static void CalibrateGain(int range);
}


void Calibrator::Run(int range, int level, void (*callback)())
{
    callbackUpdate = callback;

    Range::Set(range);

    TimeMeterMS().Wait(1000);

    if (level == 0)
    {
        CalibratorZero(range).Run();
    }
    else if (level == 1)
    {
        CalibrateGain(range);
    }
}


void Calibrator::CalibratorZero::Run()
{
    const int zero = cal.GetZero(range);

    float dc = CalculateDC(0);

    float dc1000 = CalculateDC(1000);

    int z = 0;

    int delta = (dc1000 > dc) ? 1000 : -1000;                              // �� ��� �������� ����� ����������� ���� � ������ ��������

    {
        for (int i = 0; i < 4; i++)
        {
            float sign = Math::Sign(dc);

            while (std::fabsf(sign - Math::Sign(dc)) < 1e-3f)
            {
                callbackUpdate();

                dc = CalculateDC(z);

                if (std::fabsf(dc) < 1e-10f)
                {
                    break;
                }

                z += delta;
            }

            delta = -delta / 10;
        }
    }

    bool correct_ac = false;

    LOG_WRITE("z = %d, ac = %e, dc = %e", z, (double)Calculator::GetAC(&correct_ac), (double)dc);

    if (Math::Abs(z) < 10000)
    {
        cal.SetZero(range, z);
    }
    else
    {
        cal.SetZero(range, zero);
    }
}


float Calibrator::CalibratorZero::CalculateDC(int zero)
{
    cal.SetZero(range, zero);

    Ampermeter::MeasurementCycle();
    Calculator::AppendData();

    bool correct_dc = false;

    return Calculator::GetDC(&correct_dc);
}


void Calibrator::CalibrateGain(int range)
{
    cal.SetGainK(range, 1.0f);

    Ampermeter::MeasurementCycle();
    Calculator::AppendData();

    bool correct_dc = false;

    float dc = std::fabsf(Calculator::GetDC(&correct_dc));

    float k = Range::Max(range) / dc;

    if (range < 3)
    {
        k *= 1e3f;
    }

    cal.SetGainK(range, k);

    LOG_WRITE("range = %d, dc = %f, k = %f", range, (double)dc, (double)k);
}


void Calibrator::PressButtonSave()
{
    cal.Save();
}
