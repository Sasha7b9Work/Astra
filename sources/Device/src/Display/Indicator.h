// 2022/10/28 11:17:39 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
*  ���� ��������� ���������
*/


namespace Indicator
{
    void Update();

    // ����� ���� ������� ������������� ������ ������������� � ����������� �� ������������� �������
    void AutoSize();

    void SetMeasures(float dc, float ac, int range);

    void OnCnageRangeEvent();

    void SetDeltaADC(float);
}
