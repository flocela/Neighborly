#include "GrDiversityPrinter.h"
#include <iostream>

GrDiversityPrinter::GrDiversityPrinter (
    GrDiversityPrinterSizer grDivPrSizer,
    std::unordered_map<int, Color> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int largestNumOfNeighbors
) : _res_colors{resColors},
    _top_left_x__px{topLeftCornerXPx},
    _top_left_y__px{topLeftCornerYPx},
    _given_space_x__px{grDivPrSizer.getXSpaceLengthPx()},
    _given_space_y__px{grDivPrSizer.getYSpaceLengthPx()},
    _format_x{grDivPrSizer.getAxisFormatX()},
    _format_y{grDivPrSizer.getAxisFormatX()},
    _title_letter{grDivPrSizer.getTitleLetter()},
    _zero_run_idx{grDivPrSizer.getMinX()},
    _last_run_idx{100},
    //_last_run_idx{grDivPrSizer.getMaxX()},
    _num_of_runs{_last_run_idx - _zero_run_idx + 1},
    _largest_num_of_neighbors{largestNumOfNeighbors}
    
{  
    _format_x.setOffsetPx(_offset_multiplier * _point_size__px);
    _format_x.setOverrunPx(_override_multiplier * _point_size__px);
    _format_y.setOffsetPx(_offset_multiplier * _point_size__px);
    _format_y.setOverrunPx(_override_multiplier * _point_size__px);
    _format_y.setTitleLetterHeight(0);
    
    int runDiff = _last_run_idx - _zero_run_idx;

    // Space required if there is no space between points.
    // Center-to-center space for points is _point_size__px.
    int xRequiredSpace = 
        _format_y.getAxisHeightPx() +
        _point_size__px * (_offset_multiplier + _override_multiplier + runDiff);

    if (xRequiredSpace > _given_space_x__px)
    {
        // throw and exception
    }

    int yRequiredSpacePx =
        _format_x.getAxisHeightPx() +
        _point_size__px * (_offset_multiplier + _override_multiplier + _largest_num_of_neighbors);

    if (yRequiredSpacePx > _given_space_y__px)
    {
        // throw an exception
    }

    // X axis values
    _x_point_spacing__px = 
        (_given_space_x__px - 
        _format_y.getAxisHeightPx() -
        (_point_size__px * (_offset_multiplier + _override_multiplier)))
        /runDiff;

    int xNumOfPixelsUsed = 
        _format_y.getAxisHeightPx() +
        (_point_size__px * (_offset_multiplier + _override_multiplier)) +
        (_x_point_spacing__px * runDiff);

    _cross_x__px = 
        _top_left_x__px +
        ((_given_space_x__px - xNumOfPixelsUsed)/2) +
        _format_y.getAxisHeightPx();

    // Y axis values
    _y_point_spacing__px = 
        (_given_space_y__px -
        _title_letter.getHeightIncLSpace() -
        _format_x.getAxisHeightPx() -
        (_point_size__px * (_offset_multiplier + _override_multiplier)))
        /_largest_num_of_neighbors;

    _cross_y__px = _top_left_y__px + _given_space_y__px -_format_x.getAxisHeightPx();

    // Place titles
    _title_x__px = xNumOfPixelsUsed/2;
    _title_y__px = _top_left_y__px;

    // tick and label spacing
    _min_tick_spacing_x = ( _num_of_runs <= 100 )? 1 : 5;
    _maj_tick_spacing_x = ( _num_of_runs <= 100 )? 1 : 5;
    _min_tick_spacing_y = (_largest_num_of_neighbors + 1 < 10)? 1 : 1; // TODO maybe something haveing to do with odd and even would be better.
    _maj_tick_spacing_y = (_largest_num_of_neighbors + 1 < 10)? 2 : 5;
    _label_spacing_x = ( _num_of_runs <= 10 )? 1 : 10;
    _label_spacing_y = (_largest_num_of_neighbors + 1 < 10)? 2 : 5;
    _pixel_converter_x = createPixelConverterX();
    _pixel_converter_y = createPixelConverterY();

    addXAxis();
    addYAxis();
}

void GrDiversityPrinter::print (
    std::unordered_map<int,std::vector<int>> _num_of_like_diff_per_group,
    Renderer* renderer
)
{   /*std::vector<SDL_Rect> rects = {};
    
    SDL_Rect rect1;
    rect1.w = 10;
    rect1.h = _given_space_y__px;
    rect1.x = _top_left_x__px + 50;
    rect1.y = _top_left_y__px;

    renderer->setColorToRed();
    rects.push_back(rect1);
    renderer->fillBlocks(rects);*/

    (void)_num_of_like_diff_per_group;
    _x_axis->print(renderer);
    _y_axis->print(renderer);
    printTitle(renderer);
}

void GrDiversityPrinter::addXAxis ()
{   
    _x_axis = std::make_unique<XAxisL2RBottom>(
        "", // no axis title
        _pixel_converter_x.get(),
        _format_x,
        _cross_x__px,
        _cross_y__px,
        _zero_run_idx,
        _last_run_idx,
        _maj_tick_spacing_x,
        _min_tick_spacing_x,
        _label_spacing_x
    );

}

void GrDiversityPrinter::addYAxis ()
{
    _y_axis = std::make_unique<YAxisB2T>(
        "",
        _pixel_converter_y.get(),
        _format_y,
        _cross_x__px,
        _cross_y__px,
        0,
        _largest_num_of_neighbors,
        _maj_tick_spacing_y, 
        _min_tick_spacing_y,
        _label_spacing_y,
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

std::unique_ptr<PixelConverter> GrDiversityPrinter::createPixelConverterX ()
{
    int maxXAxisPixel = 
        _cross_x__px + 
        (_offset_multiplier * _point_size__px) + 
        (_x_point_spacing__px) * (_last_run_idx - _zero_run_idx);

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
        (_y_point_spacing__px) * (_largest_num_of_neighbors); // range of neighbors is zero to largest
    
    return std::make_unique<PixelConverter>(
        0,
        _cross_y__px - _offset_multiplier * _point_size__px,
        _largest_num_of_neighbors,
        maxYAxisPixel
    );
}