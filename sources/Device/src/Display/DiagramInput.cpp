// 2022/10/19 09:03:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/DiagramInput.h"
#include "Display/DiagramFFT.h"
#include "Display/Painter.h"
#include "Display/DInterface.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/Timer.h"
#include <limits>


namespace DiagramInput
{
    bool NeedDraw();

    static BufferADC data;

    static const int num_points = 783;      // ������� ����� ������� ���������
    static const float height = 256;        // ����� ������ �� ���
    static const float y0 = 128;
    static bool enabled = false;
    static uint time_next_draw = 0;         // ����� ��������� ��������� ��������
}


void DiagramInput::SetData(const BufferADC &_data)
{
    data = _data;
}


bool DiagramInput::NeedDraw()
{
    if (HAL_TIM::TimeMS() < time_next_draw)
    {
        return false;
    }

    time_next_draw = HAL_TIM::TimeMS() + 500;

    return true;
}


void DiagramInput::Draw()
{
    if (!IsEnabled() || !NeedDraw())
    {
        return;
    }

    float scale = height / (data.MaxReal() - data.MinReal());
    double ave = (data.MaxReal() + data.MinReal()) / 2.0;

    uint8 points[num_points];

    for (int i = 0; i < num_points; i++)
    {
        double value = y0 + scale * (data.At(i) - ave);

        if (value < 0)
        {
            value = 0;
        }
        else if (value > 255)
        {
            value = 255;
        }

        points[i] = (uint8)value;
    }

    Painter::WaveInput::Draw(points, num_points);
}


void DiagramInput::Enable(bool _enable)
{
    if (enabled == _enable)
    {
        return;
    }

    time_next_draw = 0;

    enabled = _enable;

    Painter::WaveFFT::Disable(0);
    Painter::WaveFFT::Disable(1);
    Painter::WaveInput::Disable(0);

    if (enabled)
    {
        if (DiagramFFT::IsEnabled())
        {
            Painter::WaveFFT::Enable(0);
            Painter::WaveInput::Enable(0);
        }
        else
        {
            Painter::WaveInput::Enable(1);
        }
    }
    else
    {
        if (DiagramFFT::IsEnabled())
        {
            Painter::WaveFFT::Enable(1);
        }
    }
}


bool DiagramInput::IsEnabled()
{
    return enabled;
}


void DiagramInput::Repaint()
{
    time_next_draw = 0;
}
