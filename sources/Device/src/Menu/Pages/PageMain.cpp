// 2022/10/24 12:17:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Ampermeter/InputRelays.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include "Nextion/Nextion.h"
#include "Ampermeter/Ampermeter.h"
#include "Display/Display.h"
#include "Settings/Settings.h"
#include <cstdio>


namespace PageMain
{
    WindowMeasure wndDC(TypeMeasure::DC, "titleDC", "f_sign", "valueDC", "unitsDC", "DC:");
    WindowMeasure wndAC(TypeMeasure::AC, "titleAC", "",       "valueAC", "unitsAC", "AC:");

    static WindowMeasure wndAMPL(TypeMeasure::Ampl, "t23", "", "t10", "t27", "Iamp:");
    static WindowMeasure wndPEAK(TypeMeasure::Peak, "t20", "", "t9", "t26", "Ipp:");
    static WindowMeasure wndMIN(TypeMeasure::Min, "t22", "", "t8", "t25", "Imin:");
    static WindowMeasure wndMAX(TypeMeasure::Max, "t21", "", "t7", "t24", "Imax:");

    static void ResetAllMeasures()
    {
        wndDC.Reset();
        wndAC.Reset();
        wndAMPL.Reset();
        wndPEAK.Reset();
        wndMIN.Reset();
        wndMAX.Reset();
    }

    void Init()
    {
    }

    void OnEventChangeRange()
    {
        ResetAllMeasures();
    }

    static void FuncOnEnter()
    {
        ResetAllMeasures();

        int range = Range::Current();

        if (range > 0)
        {
            Range::Set(range - 1);
            Range::Set(range);
        }
        else
        {
            Range::Set(range + 1);
            Range::Set(range);
        }

        for (int i = 0; i < 6; i++)
        {
            char name[32];
            std::sprintf(name, "bt%d", i);
            Nextion::Button::SetValue(name, Range::Current() == i ? 1 : 0);
        }
    }

    static void FuncDraw()
    {
        Display::LabelStar::Update();

        wndDC.Draw(Ampermeter::GetDC(), Range::Current());

        wndAC.Draw(Ampermeter::GetAC(), Range::Current());

        wndAMPL.Draw(Ampermeter::GetAmpl(), Range::Current());
        wndPEAK.Draw(Ampermeter::GetPeak(), Range::Current());
        wndMIN.Draw(Ampermeter::GetMin(), Range::Current());
        wndMAX.Draw(Ampermeter::GetMax(), Range::Current());
    }


    static Button btn2mA("bt0", "01P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(0);
        });

    static Button btn2maAVP("t11", "01A", []()
        {
            Ampermeter::AVP::Enable();
            Nextion::SetVisible("t11", true);
        });

    static Button btn20mA("bt1", "02P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(1);
        });

    static Button btn20maAVP("t12", "02A", []()
        {
            Ampermeter::AVP::Enable();
        });

    static Button btn200mA("bt2", "03P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(2);
        });

    static Button btn200maAVP("t13", "03A", []()
        {
            Ampermeter::AVP::Enable();
        });

    static Button btn2A("bt3", "04P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(3);
        });

    static Button btn2aAVP("t14", "04A", []()
        {
            Ampermeter::AVP::Enable();
        });

    static Button btn20A("bt4", "05P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(4);
        });

    static Button btn50A("bt5", "06P", []()
        {
            Ampermeter::AVP::Disable();
            Range::Set(5);
        });

    static Button btnAC_DC("b0", "0AD", []()            // ������� � AC+DC
        {
            MeasuresOnDisplay::Set(MeasuresOnDisplay::AC_DC);
        });

    static Button btnAC("b0", "0AC", []()              // ������� � AC
        {
            MeasuresOnDisplay::Set(MeasuresOnDisplay::AC);
        });

    static Button btnDC("b0", "0DC", []()              // ������� � DC
        {
            MeasuresOnDisplay::Set(MeasuresOnDisplay::DC);
        });

    static Button btnCalibration("bt13", "0C", []()
        {
            PageCalibration::self->SetAsCurrent();
        });

    static Button btnSettings("bt7", "0T", []()
        {
            PageSettings::self->SetAsCurrent();
        });

    static Button btnZeroDC_EN("bt11", "0DZ1", []()         // ��������� ������ "Zero DC"
        {
            Ampermeter::Set::ZeroDC::Enable();
        });

    static Button btnZeroDC_DIS("bt11", "0DZ0", []()        // ���������� ������ "Zero DC"
        {
            Ampermeter::Set::ZeroDC::_Disable();
        });

    static Button btnZeroAC_EN("bt10", "0AZ1", []()         // ��������� ������ "Zero AC"
        {
            Ampermeter::Set::ZeroAC::Enable();
        });

    static Button btnZeroAC_DIS("bt10", "0AZ0", []()        // ���������� ������ "Zero AC"
        {
            Ampermeter::Set::ZeroAC::_Disable();
        });

    static Button btnSignal("bt12", "0S", []()              // Signal
        {
            PageGraph::self->SetAsCurrent();
        });

    static Button btnMAX("bt15", "01I", []() {});           // Imax

    static Button btnAMP("bt19", "04I", []() {});           // Iamp

    static Button btnMIN("bt18", "02I", []() {});           // Imin

    static Button btnPEAK("bt17", "03I", []() {});          // Ipp

    static Button *buttons[] =
    {
        &btn2mA,
        &btn20mA,
        &btn200mA,
        &btn2A,
        &btn20A,
        &btn50A,
        &btnAC_DC,
        &btnAC,
        &btnDC,
        &btnCalibration,
        &btnZeroDC_EN,
        &btnZeroDC_DIS,
        &btnZeroAC_EN,
        &btnZeroAC_DIS,
        &btnSignal,
        &btnMAX,
        &btnAMP,
        &btnMIN,
        &btnPEAK,
        &btnSettings,
        &btn2maAVP,
        &btn20maAVP,
        &btn200maAVP,
        &btn2aAVP,
        nullptr
    };

    static Page pageMain(buttons, FuncOnEnter, FuncDraw);

    Page *self = &pageMain;

    void SetRange(MeasuresOnDisplay::E meas, int range)
    {
        MeasuresOnDisplay::Set(meas);

        if (MeasuresOnDisplay::IsAC_DC())
        {
            btnAC_DC.SetText("AC+DC");
        }
        else if (MeasuresOnDisplay::IsAC())
        {
            btnAC_DC.SetText("AC");
        }
        else if (MeasuresOnDisplay::IsDC())
        {
            btnAC_DC.SetText("DC");
        }

        wndAC.SetVisible(MeasuresOnDisplay::IsAC_DC() || MeasuresOnDisplay::IsAC());
        wndDC.SetVisible(MeasuresOnDisplay::IsAC_DC() || MeasuresOnDisplay::IsDC());

        for (int i = 0; i < 6; i++)
        {
            PageMain::self->GetButton(i)->SetValue(i == range ? 1 : 0);
        }

        PageMain::self->GetButton(range)->Press();
    }


    void HightLightCurrentRange()
    {
        PageMain::self->GetButton(Range::Current())->SetValue(1);
    }
}


void PageMain::EnableZero(MeasuresOnDisplay::E meas, bool enable)
{
    if (meas == MeasuresOnDisplay::AC)
    {
        btnZeroAC_EN.SetValue(enable ? 1 : 0);

        enable ? btnZeroAC_EN.Press() : btnZeroAC_DIS.Press();

        Nextion::Text::SetVisible("tzAC", enable);
    }
    else if (meas == MeasuresOnDisplay::DC)
    {
        btnZeroDC_EN.SetValue(enable ? 1 : 0);

        enable ? btnZeroDC_EN.Press() : btnZeroDC_DIS.Press();

        Nextion::Text::SetVisible("tzDC", enable);
    }
}
