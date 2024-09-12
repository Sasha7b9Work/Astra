// 2022/11/14 13:39:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Settings/CalibrationSettings.h"
#include "Settings/Settings.h"


struct Lang
{
    enum E
    {
        RU,
        EN,
        Count
    };
};


struct TypeMeasure
{
    enum E
    {
        DC,
        AC,
        Ampl,
        Peak,
        Min,
        Max,
        Frequency,
        Count
    };

    TypeMeasure(E v) : value(v) { }

    bool ExistFieldSign() const;

    pchar Title(Lang::E lang) const;

    bool IsShown() const;

private:

    E value;
};


// ��� ��������� �� �������
struct MeasuresOnDisplay
{
    enum E
    {
        AC_DC,
        AC,
        DC,
        Count
    };

    static void Set(E v) { current = v; }

    static bool IsAC_DC() { return current == AC_DC; }
    static bool IsAC() { return current == AC; }
    static bool IsDC() { return current == DC; }

    static E current;
};


struct Baudrate
{
    enum E
    {
        _9600,
        _115200
    };
};


struct Parity
{
    enum E
    {
        No,
        Yes
    };
};


struct StopBits
{
    enum E
    {
        _1,
        _1_5,
        _2
    };
};


struct ChangeRange
{
    enum E
    {
        Hand,
        Auto
    };
};


struct RangeFreq
{
    enum E
    {
        Low,
        Middle,
        Hi
    };
};


struct Settings
{
    uint size;          // ����� ������ �������� - ��� �������� ����, ��� ������ �������������
    uint crc32;         // ����� ����������� ����� - ��� �������� ������������ ����������

    bool middle_of_3;   // �������� ���������� �������
    bool smooth;        // ��������� ����������� �� �������� ������
    bool firLPF;        // ������� �������� ���

    bool en_DC;         // �������� ��������� ��������� DC
    bool en_AC;         // �������� ��������� ��������� ��

    TypeMeasure::E en_add_meas[3];  // ����� �������� ���������, ������� ����� �������� �� �����. ������ ��������� - ������� ������ �����, �.�. ���
                                    // ����� �������, ��������� � ����� ����� ������ ���������

    Baudrate::E baudrate;
    Parity::E parity;
    StopBits::E stop_bits;
    ChangeRange::E change_range;
    RangeFreq::E range_freq;
    int16 brightness;               // ������� �� 10 �� 100

    uint serial_number;

    Lang::E lang;

    void Save();
    void Load();

    uint CalculateCRC32() const;
    bool IsEqual(const Settings *) const;

    const uint8 *PointerToFirstData() const;
    uint SizeData() const;

    struct Storage
    {
        static void Store(const Settings &);
        static void Restore(Settings &);
    };
};


extern Settings set;
