#include "GrDiversityPrinter.h"
#include <iostream>

GrDiversityPrinter::GrDiversityPrinter (
    GrDiversityPrinterSizer grDivPrSizer,
    std::unordered_map<int, Color> resColors,
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
    _last_run_idx{100},
    //_last_run_idx{grDivPrSizer.getMaxX()}, // TODO put this back
    _num_of_runs{_last_run_idx - _zero_run_idx + 1},
    _length_of_y_axis__px{_y_given_space__px - _axis_format_X.getHeightOfAxisPx()},
    _largest_num_of_neighbors{largestNumOfNeighbors}
    
{  
    _axis_format_X.setOffsetPx(_offset_multiplier * _point_size__px);
    _axis_format_X.setOverrunPx(_override_multiplier * _point_size__px);
    _axis_format_Y.setOffsetPx(_offset_multiplier * _point_size__px);
    _axis_format_Y.setOverrunPx(_override_multiplier * _point_size__px);
    _axis_format_Y.setTitleLetterHeight(0);
    //int xAxisSpaceAllowed = _x_given_space__px - _axis_format_Y.getHeightOfAxisPx();
    int runDiff = _last_run_idx - _zero_run_idx;
    int xRequiredSpace = 
        _axis_format_Y.getHeightOfAxisPx() +
        _point_size__px * (_offset_multiplier + _override_multiplier + runDiff);

    if (xRequiredSpace > _x_given_space__px)
    {
        // throw and exception
    }

    // spacing from center of point to center of point
    _run_skip_x = 1;
    _x_point_spacing__px = 
        (_x_given_space__px - 
        _axis_format_Y.getHeightOfAxisPx() -
        (_point_size__px * (_offset_multiplier + _override_multiplier)))
        /runDiff;
    std::cout << "x_point_spacing__px: " << _x_point_spacing__px << std::endl;
    std::cout << "y.getHeightOfAxisPx(): " << _axis_format_Y.getHeightOfAxisPx() << std::endl;
    std::cout << "offset, override, rundif: " << _offset_multiplier << ", " << _override_multiplier << ", " << runDiff << std::endl;
    std::cout << "_point_size__px: " << _point_size__px << std::endl;
    int xNumOfPixelsUsed = 
        _axis_format_Y.getHeightOfAxisPx() +
        (_point_size__px * (_offset_multiplier + _override_multiplier)) +
        (_x_point_spacing__px * runDiff);
    std::cout << "GrDiversityPrinter AA" << std::endl;

/*
    int xOffsetAndOverride = _point_size__px * (_offset_multiplier + _override_multiplier);
    int xAxisSpaceRequiredPx =  
        xOffsetAndOverride + 
        _point_size__px * (_last_run_idx - _zero_run_idx);

    int totalNumberOfPixelsUsedX = 0;
    if (xAxisSpaceAllowed >= xAxisSpaceRequiredPx)
    {
        _run_skip_x = 1;

        _x_point_spacing__px = 
            (xAxisSpaceAllowed - xOffsetAndOverride)/(_last_run_idx - _zero_run_idx);
            
        totalNumberOfPixelsUsedX = 
            xOffsetAndOverride +
            _x_point_spacing__px * (_last_run_idx - _zero_run_idx);
    }
    else
    {
        // throw an exception
    }*/
    std::cout << "_x_given_space__px, xNumOfPixelsUsed: " << _x_given_space__px << ", " << xNumOfPixelsUsed << std::endl;
    _cross_x__px = 
        _top_left_corner_x__px +
        ((_x_given_space__px - xNumOfPixelsUsed)/2) +
        _axis_format_Y.getHeightOfAxisPx();
    std::cout << "_cross_x__px: " << _cross_x__px << std::endl;
    _cross_y__px = _top_left_corner_y__px + _y_given_space__px - _axis_format_X.getHeightOfAxisPx();

    _title_x__px = xNumOfPixelsUsed/2;
    _title_y__px = _top_left_corner_y__px;
    std::cout << "GrDiversityPrinter BB" << std::endl;
    int yAxisSpacedAllowed = 
        _y_given_space__px - 
        _title_letter.getHeightIncLSpace() - 
        _axis_format_Y.getHeightOfAxisPx();

    int yAxisSpaceRequiredPx = 
        _point_size__px * 
        (_largest_num_of_neighbors +
        _offset_multiplier + 
        _override_multiplier);

    if (yAxisSpacedAllowed > yAxisSpaceRequiredPx)
    {
        _y_point_spacing__px = 
            (yAxisSpacedAllowed - yAxisSpaceRequiredPx)/(_largest_num_of_neighbors + 1);
    }
    // TODO else throw an exception.

    _min_tick_spacing_x = calcMinTickSpacingX();
    _maj_tick_spacing_x = calcMajTickSpacingX();
    _min_tick_spacing_y = calcMinTickSpacingY();
    _maj_tick_spacing_y = calcMajTickSpacingY();
    _label_spacing_x = calcLabelSpacingX();
    _label_spacing_y = calcLabelSpacingY();
    std::cout << "GrDivPrinter, x_point_spacing__px: " << _x_point_spacing__px << std::endl;
    _pixel_converter_x = createPixelConverterX();
    _pixel_converter_y = createPixelConverterY();

    
    addXAxis();
    addYAxis();
    std::cout << "GrDiversityPrinter CC" << std::endl;
}

void GrDiversityPrinter::print (
    std::unordered_map<int,std::vector<int>> _num_of_like_diff_per_group,
    Renderer* renderer
)
{   /*std::vector<SDL_Rect> rects = {};
    
    SDL_Rect rect1;
    rect1.w = _x_given_space__px;
    rect1.h = 5;
    rect1.x = _top_left_corner_x__px;
    rect1.y = 900;

    renderer->setColorToRed();
    rects.push_back(rect1);
    renderer->fillBlocks(rects);*/

    std::cout << "GrDiversityPrinter DD" << std::endl;
    (void)_num_of_like_diff_per_group;
    _x_axis->print(renderer);
    std::cout << "GrDiversityPrinter EE" << std::endl;
    _y_axis->print(renderer);
    printTitle(renderer);


}

void GrDiversityPrinter::addXAxis ()
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
        calcMajTickSpacingY(), //TODO this has already been calculated
        calcMinTickSpacingY(), //TODO this has already been calculated.
        calcLabelSpacingY(),
        1,
        0
    );
}

void GrDiversityPrinter::printTitle (Renderer* renderer){
    renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _title_letter.letterHeight());
    renderer->renderText(_title_x__px, _title_y__px, _main_title, 1);
}

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
    return ( ((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 100)? 1 : 5;
 }
        
int GrDiversityPrinter::calcMinTickSpacingX ()
{
    return ( ((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 100)? 1 : 5;
}

int GrDiversityPrinter::calcMajTickSpacingY ()
 {
    return (_largest_num_of_neighbors + 1 < 10)? 2 : 5;
 }
        
int GrDiversityPrinter::calcMinTickSpacingY ()
{
    return (_largest_num_of_neighbors + 1 < 10)? 1 : 1; // TODO maybe something haveing to do with odd and even would be better.
}

int GrDiversityPrinter::calcLabelSpacingX ()
{
    return (((_last_run_idx - _zero_run_idx + 1)/_run_skip_x) <= 10)? 1 : 10;
}

int GrDiversityPrinter::calcLabelSpacingY ()
{
    return (_largest_num_of_neighbors + 1 < 10)? 2 : 5;
}

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterX ()
{
    std::cout << "_x_point_spacing__px, _cross_x__px: " << _x_point_spacing__px << ", " << _cross_x__px << std::endl;
    int maxXAxisPixel = 
        _cross_x__px + 
        (_offset_multiplier * _point_size__px) + 
        (_x_point_spacing__px) * (_last_run_idx - _zero_run_idx); // TODO put in _run_skip_x
    std::cout << "xConverter: maxXAxisPixel: " << maxXAxisPixel << std::endl;
    return std::make_unique<PixelConverter>(
        _zero_run_idx,
        _cross_x__px + _offset_multiplier * _point_size__px,
        _last_run_idx,
        maxXAxisPixel
    );
    
}

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterY ()
{
    int maxYAxisPixel = 
        _cross_y__px -
        _offset_multiplier * _point_size__px -
        (_point_size__px + _y_point_spacing__px) * (_largest_num_of_neighbors); // range of neighbors is zero to largest
    
    return std::make_unique<PixelConverter>(
        0,
        _cross_y__px - _offset_multiplier * _point_size__px,
        _largest_num_of_neighbors,
        maxYAxisPixel
    );
}