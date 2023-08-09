#include "GrAxis.h"

using namespace std;
GrAxis::GrAxis (
    unique_ptr<Axis> axis,
    AxisFormat axisFormat
): _axis{move(axis)},
   _axis_format{axisFormat}
{}

void GrAxis::print (Renderer* renderer) const
{
    std::vector<Rect> horizLinesMaj = {};
    std::vector<Rect> horizLinesMin = {};
    std::vector<Rect> ticks = {};
    std::vector<TextRect> texts = {};

    implimentAddAxisLine(ticks);
    
    implimentAddTicksAndLabels (horizLinesMaj, horizLinesMin, ticks, texts);

    if (_axis_format.showBackgroundTickLines())
    {
        renderer->fillBlocks(horizLinesMaj, _axis_format.tickLineBackgroundColor());
        renderer->fillBlocks(horizLinesMin, _axis_format.tickLineBackgroundColor());
    }

    renderer->fillBlocks(ticks, _axis_format.tickColor());
    
    renderer->renderTexts(texts);
}
