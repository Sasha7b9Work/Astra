// 2022/11/16 10:05:33 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Settings/Settings.h"


void HAL_EEPROM::Save(CalibrationSettings *)
{

}


bool HAL_EEPROM::Load(CalibrationSettings *)
{
    return false;
}


void HAL_EEPROM::Save(Settings *)
{

}


bool HAL_EEPROM::Load(Settings *)
{
    return false;
}
