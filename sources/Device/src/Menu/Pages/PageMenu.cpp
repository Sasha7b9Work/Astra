// 2024/09/09 13:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Nextion/Display.h"


namespace PageMenu
{
    static void FuncDraw()
    {

    }


    static ButtonToggle btnFrequency("�������", "Frequency", Font::_1,
        {ButtonCommon::GetCoordX(1), ButtonCommon::GetCoordY(0), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU},
        [](Item *item, bool press)
    {
        if (press)
        {
            set.en_f = item->ToButtonToggle()->IsPressed();
        }
    });

    static ButtonToggle btnImin("I���", "Imin", Font::_1,
        { ButtonCommon::GetCoordX(1), ButtonCommon::GetCoordY(1), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *item, bool press)
    {
        if (press)
        {
            set.en_Imin = item->ToButtonToggle()->IsPressed();
        }
    });

    static ButtonToggle btnImax("I����", "Imax", Font::_1,
        { ButtonCommon::GetCoordX(1), ButtonCommon::GetCoordY(2), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *item, bool press)
    {
        if (press)
        {
            set.en_Imax = item->ToButtonToggle()->IsPressed();
        }
    });

    static ButtonToggle btnIamp("I���", "Iamp", Font::_1,
        { ButtonCommon::GetCoordX(1), ButtonCommon::GetCoordY(3), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *item, bool press)
    {
        if (press)
        {
            set.en_Iampl = item->ToButtonToggle()->IsPressed();
        }
    });

    static ButtonToggle btnIpeak("I��", "Ipp", Font::_1,
        { ButtonCommon::GetCoordX(1), ButtonCommon::GetCoordY(4), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *item, bool press)
    {
        if (press)
        {
            set.en_Ipp = item->ToButtonToggle()->IsPressed();
        }
    });

    static ButtonPress btnSettings("���������", "Settings", Font::_1,
        { ButtonCommon::GetCoordX(0), ButtonCommon::GetCoordY(0), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU},
        [](Item *, bool)
    {
    });

    static ButtonPress btnSystem("�������", "System", Font::_1,
        { ButtonCommon::GetCoordX(0), ButtonCommon::GetCoordY(1), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *, bool)
    {
    });

    static ButtonToggle btnIndication("���������", "Indication", Font::_1,
        { ButtonCommon::GetCoordX(0), ButtonCommon::GetCoordY(2), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *, bool press)
    {
        btnFrequency.SetShown(press);
        btnImin.SetShown(press);
        btnImax.SetShown(press);
        btnIamp.SetShown(press);
        btnIpeak.SetShown(press);
    });

    static ButtonPress btnCalibration("����������", "Calibration", Font::_1,
        { ButtonCommon::GetCoordX(0), ButtonCommon::GetCoordY(3), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *, bool)
    {
    });

    static ButtonPress btnGraphics("�������", "Graphs", Font::_1,
        { ButtonCommon::GetCoordX(0), ButtonCommon::GetCoordY(4), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *, bool)
    {
    });

    static ButtonPress btnBack("�����", "Back", Font::_1,
        { Display::WIDTH - ButtonCommon::WIDTH_MENU - 10, ButtonCommon::GetCoordY(0), ButtonCommon::WIDTH_MENU, ButtonCommon::HEIGHT_MENU },
        [](Item *, bool press)
    {
        if (!press)
        {
            PageMain::self->SetAsCurrent();
        }
    });

//    static ButtonPress btnChangeRange("������", "Hand", Font::_1,
//        { })


    static Item *items[] =
    {
        &btnFrequency,
        &btnImin,
        &btnImax,
        &btnIamp,
        &btnIpeak,
        &btnSettings,
        &btnSystem,
        &btnIndication,
        &btnCalibration,
        &btnGraphics,
        &btnBack,
        nullptr
    };

    static void FuncOnEnter()
    {
        btnFrequency.SetToggled(set.en_f);
        btnImax.SetToggled(set.en_Imax);
        btnImin.SetToggled(set.en_Imin);
        btnIamp.SetToggled(set.en_Iampl);
        btnIpeak.SetToggled(set.en_Ipp);

        btnIndication.SetToggled(false);

//        btnFrequency.SetShown(false);
//        btnImax.SetShown(false);
//        btnImin.SetShown(false);
//        btnIamp.SetShown(false);
//        btnIpeak.SetShown(false);
    }


    static Page pageMenu(items, FuncOnEnter, FuncDraw);

    Page *self = &pageMenu;
}
