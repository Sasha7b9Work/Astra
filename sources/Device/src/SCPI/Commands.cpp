// 2022/11/23 12:38:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "SCPI/Commands.h"
#include "Device.h"
#include "Menu/Pages/Pages.h"
#include "Display/Indicator.h"


namespace SCPI
{
    void Send(pchar);

    void Error(pchar);
}


bool SCPI::Command::Execute()
{
    return false;
}


bool SCPI::CommandWithParameters::Execute()
{
    return false;
}


bool SCPI::CommandIDN::Execute()
{
    Send("OAO MNIPI, A101");
    return true;
}


bool SCPI::CommandRST::Execute()
{
    Device::Reset();
    return true;
}


bool SCPI::CommandRANGE::Execute()
{
    String<> char_range = params.GetWord(0);

    static const pchar titles[6] = { "2MA", "20MA", "200MA", "2A", "20A", "50A" };

    for (int i = 0; i < 6; i++)
    {
        if (char_range == titles[i])
        {
            PageMain::self->GetButton(i)->Press();

            return true;
        }
    }

    Error(params.c_str());

    return true;
}


bool SCPI::CommandDATA::Execute()
{
    String<> char_num = params.GetWord(0);

    int num = 0;

    if (char_num.ToInt(&num))
    {
        Indicator::OnEvent::SendDataToCommunicator(num);
    }
    else
    {
        Error(params.c_str());
    }

    return true;
}
