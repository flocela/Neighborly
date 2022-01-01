#include "GraphicDiversityPrinter.h"
#include <iostream>

GraphicDiversityPrinter::GraphicDiversityPrinter (
    Renderer* renderer,
    std::set<Color> resColors,
    int verticalSpacePx,
    int horizontalSpacePx,
    int crossHairsX,
    int crossHairsY,
    int numOfRuns,
    int residentBlockPx,
    int residentBlockBorderPx,
    int residentBlockSpacingPx,
    int runSpacingPx,
    int tickSpacingX,
    int tickSpacingY,
    int tickWidthPx,
    int axesWidthPx,
    int labelSpacingX,
    int labelSpacingY,
    // space between y-axis and first run.
    int xAxisOffsetPx,
    int yAxisOffsetPx,
    // extra length of x-axis after last run in pixels.
    int xAxisOverrunPx,
    // extra length of y-axis above greatest diversity in pixels.
    int yAxisOverrunPx,
    int fontSizeTickLabels,
    int fontSizeKeyLabels,
    int fontSizeTitle
) : _renderer{renderer},
    _length_of_y_axis__px{verticalSpacePx},
    _length_of_x_axis__px{horizontalSpacePx},
    _cross_hairs_x__px{crossHairsX},
    _cross_hairs_y__px{crossHairsY},
    _num_of_runs{numOfRuns},
    _resident_block__px{residentBlockPx},
    _resident_block_border__px{residentBlockBorderPx},
    _resident_block_spacing__px{residentBlockSpacingPx},
    _run_spacing__px{runSpacingPx},
    _tick_spacing_x{tickSpacingX},
    _tick_spacing_y{tickSpacingY},
    _tick_width__px{tickWidthPx},
    _axes_width__px{axesWidthPx},
    _label_spacing_x{labelSpacingX},
    _label_spacing_y{labelSpacingY},
    _x_axis_offset__px{xAxisOffsetPx},
    _y_axis_offset__px{yAxisOffsetPx},
    _x_axis_overrun__px{xAxisOverrunPx},
    _y_axis_overrun__px{yAxisOverrunPx},
    _font_size_axes_tick_labels{fontSizeTickLabels},
    _font_size_key{fontSizeKeyLabels},
    _font_size_title{fontSizeTitle}
{   (void) resColors;
    /*
    int numOfResidentTypes = resColors.size();
    _cell_size_x__px = ( 
        _resident_block__px + 
        ( 2 * _resident_block_border__px ) +
        ( (numOfResidentTypes - 1) * _resident_block_spacing__px ) +
        ( 2 * _run_spacing__px)
    );
    _pixel_converter_x = std::make_unique<PixelConverter>(
        0,
        _cross_hairs_x__px + _x_axis_offset__px,
        _num_of_runs,
        _cross_hairs_x__px + _x_axis_offset__px + (_cell_size_x__px * _num_of_runs)
    );
    _pixel_converter_y = std::make_unique<PixelConverter>(
        0,
        _cross_hairs_y__px - _y_axis_offset__px,
        100,
        _cross_hairs_y__px - _y_axis_offset__px - _length_of_y_axis__px
    );
    addXAxis();*/
}

void GraphicDiversityPrinter::printDiversity (
    std::map<Resident*, int> resident2like, 
    std::map<Resident*, int> resident2diff
)
{
    (void)resident2like;
    (void)resident2diff;
    addXAxis();
}

void GraphicDiversityPrinter::addXAxis ()
{
    _x_axis_utility = std::make_unique<XAxisUtility>(
        "xAxis",
        _renderer,
        _pixel_converter_x.get(),
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _cell_size_x__px,
        _min_run__px,
        _max_run__px,
        _x_axis_overrun__px,
        _tick_spacing_x,
        _label_spacing_x,
        _font_size_axes_tick_labels,
        _font_size_key
    );
}


