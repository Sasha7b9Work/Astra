// 2022/10/17 15:30:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/DInterface.h"
#include "Hardware/HAL/HAL_PIO.h"
#include "Hardware/HAL/HAL.h"
#include "Menu/MenuItems.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>


/*
*  +--------+---------------+
*  | ������ | ������/������ |
*  +--------+---------------+
*  |   1    | "11Z" / "10Z" |
*  |   2    | "21Z" / "20Z" |
*  |   3    | "31Z" / "30Z" |
*  |   4    | "41Z" / "40Z" |
*  |   5    | "51Z" / "50Z" |
*  |   6    | "61Z" / "60Z" |
*  |  ����  | "71Z" / "70Z" |
*  +--------+---------------+
*/


namespace Display
{
    namespace Interface
    {
        static const int SIZE_BUFFER = 10;
        static uint8 buffer[SIZE_BUFFER];
        static int pointer = 0;
        static ReturnCodeDI::E last_code = ReturnCodeDI::InstructionSuccessful;

        static void DecodeBufferFF();
        static void DecodeBufferZ();
    }
}


ReturnCodeDI::E Display::Interface::LastCode()
{
    return last_code;
}


void Display::Interface::CallbackOnReceive(uint8 byte)
{
    if (byte == 0xFF)
    {
        DecodeBufferFF();
    }
    else if (byte == 'Z')
    {
        DecodeBufferZ();
    }
    else
    {
        buffer[pointer++] = byte;
    }
    
    if(pointer == SIZE_BUFFER)
    {
        pointer = pointer;
    }
}


void Display::Interface::DecodeBufferFF()
{
    if(pointer == 0)
    {
        return;
    }
    
    uint8 byte = buffer[pointer - 1];
    
    if (byte >= '1' && byte <= '8')
    {
        int button = byte & 0x0F;

        Button::ForIndex(button)->Press();
    }
    else
    {
        last_code = (ReturnCodeDI::E)byte;
        
        if (last_code == ReturnCodeDI::TransparentDataFinished)
        {
            last_code = last_code;
        }
        else if (last_code == ReturnCodeDI::TransparentDataReady)
        {
            last_code = last_code;
        }
        else
        {
            last_code = last_code;
        }
    }

    pointer = 0;
}


void Display::Interface::DecodeBufferZ()
{
    if (pointer == 0)
    {
        return;
    }

    uint8 byte = buffer[pointer - 1];

    if (byte >= '1' && byte <= '8')
    {
        int button = byte & 0x0F;

        Button::ForIndex(button)->Press();
    }
    else
    {
        last_code = (ReturnCodeDI::E)byte;

        if (last_code == ReturnCodeDI::TransparentDataFinished)
        {
            last_code = last_code;
        }
        else if (last_code == ReturnCodeDI::TransparentDataReady)
        {
            last_code = last_code;
        }
        else
        {
            last_code = last_code;
        }
    }

    pointer = 0;
}


void Display::Interface::SendCommand(pchar command)
{
    last_code = ReturnCodeDI::_None;

    HAL_USART2::Send(command);

    HAL_USART2::Send("\xFF\xFF\xFF");

//    while (last_code == ReturnCodeDI::_None)
//    {
//    }
}


void Display::Interface::SendByte(uint8 byte)
{
    last_code = ReturnCodeDI::_None;

    HAL_USART2::SendByte(byte);
}


void Display::Interface::SendCommandFormat(pchar format, ...)
{
    char message[256];

    std::va_list args;
    va_start(args, format);
    std::vsprintf(message, format, args);
    va_end(args);

    SendCommand(message);
}
