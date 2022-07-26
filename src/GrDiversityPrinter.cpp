#include "GrDiversityPrinter.h"
#include <iostream>

GrDiversityPrinter::GrDiversityPrinter (
    GrDiversityPrinterSizer grDivPrSizer,
    std::map<int, std::pair<Color, Color>> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int largestNumOfNeighbors
) : _res_colors{resColors},
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
    _length_of_x_axis__px{_x_given_space__px - _axis_format_Y.getHeightOfAxisPx()},
    _length_of_y_axis__px{_y_given_space__px - _axis_format_X.getHeightOfAxisPx()},
    _cross_x__px{_axis_format_Y.getHeightOfAxisPx()},
    _cross_y__px{_axis_format_X.getHeightOfAxisPx() + _title_letter.getHeightIncLSpace()},
    _largest_num_of_neighbors{largestNumOfNeighbors}
    
{
    std::cout << "GrDiversityPrinter constructor A" << std::endl;
    _coord_skip_x = calcCoordSkipX();
    std::cout << "GrDiversityPrinter constructor B" << std::endl;
    _min_tick_spacing_x = calcMinTickSpacingX();
    std::cout << "GrDiversityPrinter constructor C" << std::endl;
    _maj_tick_spacing_x = calcMajTickSpacingX();
    std::cout << "GrDiversityPrinter constructor D" << std::endl;
    _min_tick_spacing_y = calcMinTickSpacingY();
    std::cout << "GrDiversityPrinter constructor E" << std::endl;
    _maj_tick_spacing_y = calcMajTickSpacingY();
    std::cout << "GrDiversityPrinter constructor F" << std::endl;
    _label_spacing_x = calcLabelSpacingX();
    std::cout << "GrDiversityPrinter constructor G" << std::endl;
    _label_spacing_y = calcLabelSpacingY();
    std::cout << "GrDiversityPrinter constructor H" << std::endl;
    _pixel_converter_x = createPixelConverterX();
    std::cout << "GrDiversityPrinter constructor I" << std::endl;
    _pixel_converter_y = createPixelConverterY();
    std::cout << "GrDiversityPrinter constructor J" << std::endl;
    addXAxis();
    addYAxis();
    addTitle();
    std::cout << "GrDiversityPrinter constructor Z" << std::endl;
}

void GrDiversityPrinter::print (
    std::unordered_map<int,std::vector<int>> _num_of_like_diff_per_group,
    Renderer* renderer
)
{
    (void)_num_of_like_diff_per_group;
    _x_axis->print(renderer);
}

void GrDiversityPrinter::addXAxis ()
{
    _x_axis = std::make_unique<XAxisL2R>(
        "", // no axis title
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
        "",
        _pixel_converter_y.get(),
        _axis_format_Y,
        _cross_x__px,
        _cross_y__px,
        0,
        _largest_num_of_neighbors,
        calcMajTickSpacingY(),
        calcMinTickSpacingY(),
        calcLabelSpacingY()
    );
}

void GrDiversityPrinter::addTitle (){} //TODO

// TODO not used, delete method
int GrDiversityPrinter::calcXAxisLengthPx ()
{
    return _x_given_space__px - _axis_format_Y.getHeightOfAxisPx();
}

// TODO not used, delete method
int GrDiversityPrinter::calcYAxisLengthPx ()
{
    return _y_given_space__px - _axis_format_X.getHeightOfAxisPx() - _title_letter.getHeightIncLSpace();
}


int GrDiversityPrinter::calcCoordSkipX () //TODO put a limit on number of runs.
{   
    int numXPixels = _length_of_x_axis__px - _axis_format_X.offsetPx() - _axis_format_X.overrunPx();
   
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

// TODO not used, delete method
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
    return 2;
 }
        
int GrDiversityPrinter::calcMinTickSpacingY ()
{
    return 1;
}

int GrDiversityPrinter::calcLabelSpacingX ()
{
    return ((_num_of_runs/_coord_skip_x) <= 10)? 1 : 10;
}

int GrDiversityPrinter::calcLabelSpacingY ()
{
    return 2;
}

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterX ()
{
    int maxXAxisPixel = 
        _cross_x__px + 
        _axis_format_X.offsetPx() + 
        _data_point_size__px * _num_of_runs;
    
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
        _cross_y__px -
        _axis_format_Y.offsetPx() -
        _data_point_size__px * (_largest_num_of_neighbors + 1); // range of neighbors is zero to largest
    
    return std::make_unique<PixelConverter>(
        0,
        _cross_y__px - _axis_format_Y.offsetPx(),
        _largest_num_of_neighbors,
        maxYAxisPixel
    );
}