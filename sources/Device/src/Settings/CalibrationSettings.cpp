// 2022/11/22 08:45:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings/CalibrationSettings.h"
#include "Hardware/HAL/HAL.h"
#include <cstring>


namespace NS_CalibrationSettings
{
    static CalibrationSettings cal_def
    {
        sizeof(CalibrationSettings),
        0,
        { {0, 1.0}, {1, 1.0}, {2, 1.0}, {3, 1.0}, {4, 1.0}, {5, 1.0} },
        {  0,        0,        0,        0,        0,        0 }
    };
}


CalibrationSettings CalibrationSettings::Storage::stored;


CalibrationSettings cal = NS_CalibrationSettings::cal_def;


float CalibrationSettings::Gain::Get() const
{
    static const float k[6] = { 61.53e-2f, 61.53e-1f, 61.53e0f, 61.53e-2f, 61.53e-1f, 61.53e0f };

    return value * k[range];
}


void CalibrationSettings::Save()
{
    size = sizeof(*this);
    crc32 = CalculateCRC32();

    CalibrationSettings loaded;

    HAL_EEPROM::Load(&loaded);

    if (!loaded.IsEqual(this))
    {
        HAL_EEPROM::Save(this);
    }
}


void CalibrationSettings::Load()
{
    if (!HAL_EEPROM::Load(this))
    {
        Reset();
    }
}


void CalibrationSettings::Reset()
{
    *this = NS_CalibrationSettings::cal_def;
}


uint CalibrationSettings::CalculateCRC32() const
{
    return HAL_CRC32::Calculate(PointerToFirstData(), SizeData());
}


bool CalibrationSettings::IsEqual(const CalibrationSettings *rhs) const
{
    if (size != rhs->size)
    {
        return false;
    }

    return std::memcmp(PointerToFirstData(), rhs->PointerToFirstData(), SizeData()) == 0;
}


uint CalibrationSettings::SizeData() const
{
    return sizeof(*this) - 2 * sizeof(size);
}


const uint8 *CalibrationSettings::PointerToFirstData() const
{
    return (const uint8 *)this + 2 * sizeof(size);
}


void CalibrationSettings::Storage::Store(const CalibrationSettings &settings)
{
    stored = settings;
}


void CalibrationSettings::Storage::Restore(CalibrationSettings &settings)
{
    settings = stored;
}
