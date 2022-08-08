#include "GrHappinessPrinter.h"
#include <iostream>

GrHappinessPrinter::GrHappinessPrinter (
    GrHappinessPrinterSizer grDivPrSizer,
    std::unordered_map<int, Color> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx
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
    _length_of_y_axis__px{_y_given_space__px - _axis_format_X.getAxisHeightPx()}
    
{  
    _axis_format_X.setOffsetPx(_offset_multiplier * _point_size__px);
    _axis_format_X.setOverrunPx(_override_multiplier * _point_size__px);
    _axis_format_Y.setOffsetPx(_offset_multiplier * _point_size__px);
    _axis_format_Y.setOverrunPx(_override_multiplier * _point_size__px);
    int xAxisSpaceAllowed = _x_given_space__px - _axis_format_Y.getAxisHeightPx();
    int xAxisSpaceRequiredPx =  _point_size__px * ( 
                                (_last_run_idx - _zero_run_idx) +
                                _offset_multiplier +
                                _override_multiplier
                               );
    int totalNumberOfPixelsUsedX = 0;
    if (xAxisSpaceAllowed >= xAxisSpaceRequiredPx)
    {
        _run_skip_x = 1;

        _x_point_spacing__px = 
            (xAxisSpaceAllowed - xAxisSpaceRequiredPx)/(_last_run_idx - _zero_run_idx);
            
        totalNumberOfPixelsUsedX = 
            _point_size__px * (_offset_multiplier + _override_multiplier) +
            (_point_size__px + _x_point_spacing__px) * (_last_run_idx - _zero_run_idx);
    }
    else
    {
        // Throw and exception
    }
    _cross_x__px = _top_left_corner_x__px + ((_x_given_space__px - totalNumberOfPixelsUsedX)/2);
    _cross_y__px = _top_left_corner_y__px + _y_given_space__px - _axis_format_X.getAxisHeightPx();

    _title_x__px = _cross_x__px + (totalNumberOfPixelsUsedX/2);
    _title_y__px = _top_left_corner_y__px;

    int yAxisSpacedAllowed = 
        _y_given_space__px - 
        _title_letter.getHeightIncLSpace() - 
        _axis_format_Y.getAxisHeightPx();

    int yAxisSpaceRequiredPx = 
        _point_size__px * 
        (_largest_y +
        _offset_multiplier + 
        _override_multiplier);
        

    if (yAxisSpacedAllowed > yAxisSpaceRequiredPx)
    {
        _y_point_spacing__px = 
            (yAxisSpacedAllowed - yAxisSpaceRequiredPx)/(_largest_y + 1);
    }
    // TODO else throw an exception.

    _min_tick_spacing_x = calcMinTickSpacingX();
    _maj_tick_spacing_x = calcMajTickSpacingX();
    _min_tick_spacing_y = calcMinTickSpacingY();
    _maj_tick_spacing_y = calcMajTickSpacingY();
    _label_spacing_x = calcLabelSpacingX();
    _label_spacing_y = calcLabelSpacingY();
    _pixel_converter_x = createPixelConverterX();
    _pixel_converter_y = createPixelConverterY();

    addXAxis();
    addYAxis();
    
}

void GrHappinessPrinter::print (
    std::unordered_map<int,std::vector<int>> _num_of_like_diff_per_group,
    Renderer* renderer
)
{
    (void)_num_of_like_diff_per_group;
    _x_axis->print(renderer);
    _y_axis->print(renderer);
    printTitle(renderer);
}

void GrHappinessPrinter::addXAxis ()
{   
    _x_axis = std::make_unique<XAxisL2RBottom>(
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

void GrHappinessPrinter::addYAxis ()
{
    _y_axis = std::make_unique<YAxisB2T>(
        "",
        _pixel_converter_y.get(),
        _axis_format_Y,
        _cross_x__px,
        _cross_y__px,
        0,
        _largest_y,
        calcMajTickSpacingY(), //TODO this has already been calculated
        calcMinTickSpacingY(), //TODO this has already been calculated.
        calcLabelSpacingY(),
        0.1,
        1
    );
}

void GrHappinessPrinter::printTitle (Renderer* renderer){
    renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _title_letter.letterHeight());
    renderer->renderText(_title_x__px, _title_y__px, _main_title, 1);
    std::cout << "GrDiverstiyPrinter _titl_y__Px: " << _title_y__px << std::endl;
}

// TODO not used, delete method
int GrHappinessPrinter::calcXAxisLengthPx ()
{
    return _x_given_space__px - _axis_format_Y.getAxisHeightPx();
}

// TODO not used, delete method
int GrHappinessPrinter::calcYAxisLengthPx ()
{
    return _y_given_space__px - _axis_format_X.getAxisHeightPx() - _title_letter.getHeightIncLSpace();
}

// TODO not used, delete method
int GrHappinessPrinter::calcXCrossHairsPx ()
{
    return _axis_format_Y.getAxisHeightPx();
}

int GrHappinessPrinter::calcYCrossHairsPx ()
{
    return _axis_format_X.getAxisHeightPx() + _title_letter.getHeightIncLSpace();
}

int GrHappinessPrinter::calcMajTickSpacingX ()
 {
    return ( ((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 100)? 1 : 5;
 }
        
int GrHappinessPrinter::calcMinTickSpacingX ()
{
    return ( ((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 100)? 1 : 5;
}

int GrHappinessPrinter::calcMajTickSpacingY ()
 {
    return (_largest_y + 1 < 10)? 2 : 5;
 }
        
int GrHappinessPrinter::calcMinTickSpacingY ()
{
    return (_largest_y + 1 < 10)? 1 : 1; // TODO maybe something haveing to do with odd and even would be better.
}

int GrHappinessPrinter::calcLabelSpacingX ()
{
    return (((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 10)? 1 : 10;
}

int GrHappinessPrinter::calcLabelSpacingY ()
{
    return (_largest_y + 1 < 10)? 2 : 5;
}

std::unique_ptr<PixelConverter> GrHappinessPrinter::createPixelConverterX ()
{
    int maxXAxisPixel = 
        _cross_x__px + 
        (_offset_multiplier * _point_size__px) + 
        ((_point_size__px + _x_point_spacing__px) * (_last_run_idx - _zero_run_idx)); // TODO put in _run_skip_x
    return std::make_unique<PixelConverter>(
        _zero_run_idx,
        _cross_x__px + _offset_multiplier * _point_size__px,
        _last_run_idx,
        maxXAxisPixel
    );
    
}

std::unique_ptr<PixelConverter> GrHappinessPrinter::createPixelConverterY ()
{
    int maxYAxisPixel = 
        _cross_y__px -
        _offset_multiplier * _point_size__px -
        (_point_size__px + _y_point_spacing__px) * (_largest_y); // range of neighbors is zero to largest
    
    return std::make_unique<PixelConverter>(
        0,
        _cross_y__px - _offset_multiplier * _point_size__px,
        _largest_y,
        maxYAxisPixel
    );
}