#include "GrDiversityPrinter.h"
#include <iostream>

GrDiversityPrinter::GrDiversityPrinter (
    GrDiversityPrinterSizer grDivPrSizer,
    Renderer* renderer,
    std::map<int, std::pair<Color, Color>> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx
) : _renderer{renderer},
    _res_colors{resColors},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_given_space__px{grDivPrSizer.getXSpaceLengthPx()},
    _y_given_space__px{grDivPrSizer.getYSpaceLengthPx()},
    _axis_format_X{grDivPrSizer.getAxisFormatX()},
    _axis_format_Y{grDivPrSizer.getAxisFormatX()},
    _title_letter{grDivPrSizer.getTitleLetter()},
    _zero_run_idx{grDivPrSizer.getMinX()},
    _last_run_idx{grDivPrSizer.getMaxX()},
    _num_of_runs{_last_run_idx - _zero_run_idx + 1},
    _length_of_x_axis__px{calcXAxisLengthPx()},
    _length_of_y_axis__px{calcYAxisLengthPx()},
    _cross_x__px{calcXCrossHairsPx()},
    _cross_y__px{calcYCrossHairsPx()}
    
{
    _length_of_x_axis__px = calcXAxisLengthPx();
    _length_of_y_axis__px = calcYAxisLengthPx();
    _coord_skip_x = calcCoordSkipX();
    _coord_skip_y = calcCoordSkipY();
    _min_tick_spacing_x = calcMinTickSpacingX();
    _maj_tick_spacing_x = calcMajTickSpacingX();
    _min_tick_spacing_y = calcMinTickSpacingY();
    _maj_tick_spacing_y = calcMajTickSpacingY();
    _label_spacing_x = calcLabelSpacingX();
    _label_spacing_y = calcLabelSpacingY();
    _cross_x__px = calcXCrossHairsPx();
    _cross_y__px = calcYCrossHairsPx();
    addXAxis();
    addYAxis();
    addTitle();
}

void GrDiversityPrinter::printDiversity (
    std::map<Resident*, int> resident2like, 
    std::map<Resident*, int> resident2diff
)
{
    (void)resident2like;
    (void)resident2diff;
    //addXAxis();
}

void GrDiversityPrinter::addXAxis ()
{
    _x_axis = std::make_unique<XAxisL2R>(
        "xAxis",
        _pixel_converter_x.get(),
        _axis_format_X,
        _cross_x__px,
        _cross_y__px,
        _zero_run_idx,
        _last_run_idx,
        calcMajTickSpacingX(),
        calcMinTickSpacingX(),
        calcLabelSpacingX()
    );
}

void GrDiversityPrinter::addYAxis ()
{
    _y_axis = std::make_unique<YAxisB2T>(
        "yAxis",
        _pixel_converter_y.get(),
        _axis_format_Y,
        _cross_x__px,
        _cross_y__px,
        0,
        100,
        calcMajTickSpacingY(),
        calcMinTickSpacingY(),
        calcLabelSpacingY()
    );
}

void GrDiversityPrinter::addTitle (){} //TODO

int GrDiversityPrinter::calcXAxisLengthPx ()
{
    return _x_given_space__px - _axis_format_Y.getHeightOfAxisPx();
}

int GrDiversityPrinter::calcYAxisLengthPx ()
{
    return _y_given_space__px - _axis_format_X.getHeightOfAxisPx() - _title_letter.getHeightIncLSpace();
}


int GrDiversityPrinter::calcCoordSkipX () //TODO put a limit on number of runs.
{   
    int numXPixels = _length_of_x_axis__px - _axis_format_X.offsetPx() - _axis_format_X.overrunPx();
    int numPixelsNeededForXAxis = _num_of_runs * _data_point_size__px;
    if (numXPixels > numPixelsNeededForXAxis)
    {
        return 1;
    }
    else
    {
        int ratio = _num_of_runs/(numXPixels/_data_point_size__px);
        if (ratio < 1)
        {
            return 1;
        }
        else if (ratio < 2)
        {
            return 2;
        }
        else if (ratio < 5)
        {
            return 5;
        }
        else
        {
            return 10;
        }
    }  
}

int GrDiversityPrinter::calcCoordSkipY () // TODO put minimum space needed for Y axis.
{   
    // Y-Axis is from 0 to 100 because it is a percentage.
    int numYPixels = _length_of_y_axis__px - _axis_format_Y.offsetPx() - _axis_format_Y.overrunPx();
    int numPixelsNeededForYAxis = 100 * _data_point_size__px;
    if (numYPixels > numPixelsNeededForYAxis)
    {
        return 1;
    }
    else
    {
        int ratio = 101/(numYPixels/_data_point_size__px);
        if (ratio < 1)
        {
            return 1;
        }
        else if (ratio < 2)
        {
            return 2;
        }
        else
        {
            return 5;
        }
    }
}


int GrDiversityPrinter::calcXCrossHairsPx ()
{
    return _axis_format_Y.getHeightOfAxisPx();
}

int GrDiversityPrinter::calcYCrossHairsPx ()
{
    return _axis_format_X.getHeightOfAxisPx() + _title_letter.getHeightIncLSpace();
}

int GrDiversityPrinter::calcMajTickSpacingX ()
 {
    return ( (_num_of_runs/_coord_skip_x) <= 100)? 1 : 5;
 }
        
int GrDiversityPrinter::calcMinTickSpacingX ()
{
    return ( (_num_of_runs/_coord_skip_x) <= 100)? 1 : 5;
}

int GrDiversityPrinter::calcMajTickSpacingY ()
 {
    return ( (100/_coord_skip_y) <= 100)? 1 : 5;
 }
        
int GrDiversityPrinter::calcMinTickSpacingY ()
{
    return ( (100/_coord_skip_y) <= 100)? 1 : 5;
}

int GrDiversityPrinter::calcLabelSpacingX ()
{
    return ((_num_of_runs/_coord_skip_x) <= 10)? 1 : 10;
}

int GrDiversityPrinter::calcLabelSpacingY ()
{
    return (100/_coord_skip_y)? 1 : 10;
}

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterX ()
{
    int maxXAxisPixel = 
        _cross_x__px + 
        _axis_format_X.offsetPx() + 
        _data_point_size__px * (_num_of_runs + 1);
    
    return std::make_unique<PixelConverter>(
        _zero_run_idx,
        _cross_x__px + _axis_format_X.offsetPx(),
        _last_run_idx,
        maxXAxisPixel
    );
}

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterY ()
{
    int maxYAxisPixel = 
        _cross_y__px + 
        _axis_format_Y.offsetPx() + 
        _data_point_size__px * (101);
    
    return std::make_unique<PixelConverter>(
        0,
        _cross_y__px + _axis_format_Y.offsetPx(),
        101,
        maxYAxisPixel
    );
}