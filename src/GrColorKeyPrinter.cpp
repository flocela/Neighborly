#include "GrColorKeyPrinter.h"

void GrColorKeyPrinter::print (Renderer* renderer)
{
    int xCenter = _x_offset + (_x_space_length__px/2);

    renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _title_letter.letterHeight()
    );

    // happy Group1
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter - _x_space_from_center,_y_offset + _box_length__px/4),
        _the_color_infos[_colors[1].first].rgba
    );

    // unhappy Group1
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter -_x_space_from_center/2, _y_offset + _box_length__px/4),
        _the_color_infos[_colors[1].second].rgba
    );

    // happy Group2
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter + _box_spacer__px,_y_offset + _box_length__px/4),
        _the_color_infos[_colors[2].first].rgba
    );

    // unhappy Group2
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter +_x_space_from_center/2, _y_offset + _box_length__px/4),
        _the_color_infos[_colors[2].second].rgba
    );

    
    renderer->renderText(
        xCenter - _x_space_from_center + _box_length__px,
        _y_offset,
        "Group 1 Happy",
        4
    );

    renderer->renderText(
        xCenter - _x_space_from_center/2 + _box_length__px,
        _y_offset,
        "Group 1 Unhappy",
        4
    );

     renderer->renderText(
        xCenter + _box_spacer__px + _box_length__px,
        _y_offset,
        "Group 2 Happy",
        4
    );

    renderer->renderText(
        xCenter + _x_space_from_center/2 + _box_length__px,
        _y_offset,
        "Group 2 Unhappy",
        4
    );

}