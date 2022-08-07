#include "GrColorKeyPrinter.h"
#include <algorithm>

void GrColorKeyPrinter::print (Renderer* renderer)
{   
    //int xCenter = _x_offset + (_x_space_length__px/2);

    renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _title_letter.letterHeight()
    );

    std::vector<int> groups;
    for (std::unordered_map<int, Color>::iterator itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        groups.push_back(itr->first);
    }
    std::vector<std::string> moods;
    for (std::set<std::string>::iterator itr = _moods.begin(); itr != _moods.end(); ++itr)
    {
        std::string cur = *itr;
        moods.push_back(cur);
    }
    std::sort(groups.begin(), groups.end());
    std::sort(moods.begin(), moods.end());
    int offset = 70;
    int leftPixel = (_x_space_length__px/2) - (_x_column_width/2 * moods.size() * groups.size());
    for (int gg=0; gg<(int)groups.size(); ++gg)
    {
        if ( ( gg != 0 && gg == (int)groups.size()/2) )
        {
            leftPixel = leftPixel + offset;
        }
        for (int mm=0; mm<(int)moods.size(); ++mm)
        {    
            int group_id = groups[gg];
            Color color = _colors[group_id];
            
            renderer->addBlock(
                _box_length__px/2,
                _box_length__px/2,
                Coordinate(
                    leftPixel + (gg*moods.size() + mm)*_x_column_width,
                    _y_offset + _box_length__px/4),
                _the_color_infos[_color_map[color][moods[mm]]].rgba
            );
            std::cout << "gg, mm, color, mood: " << gg << ", " << mm << ", " << color << ", " << moods[mm] << std::endl;
            std::string text;
            if (moods[mm] == "neutral")
            {
                text = "Group: " + std::to_string(groups[gg]);
            }
            else
            {
                text = "Group: " + std::to_string(groups[gg]) + " " + moods[mm];
            }
            
            renderer->renderText(
                leftPixel + (gg*moods.size() + mm)*_x_column_width + _box_length__px,
                _y_offset,
                text,
                4
            );
        }
        
    }
/*
    // happy Group1
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter - _x_column_width,_y_offset + _box_length__px/4),
        _the_color_infos[_color_map[colors[1]]["happy"]].rgba
    );

    // unhappy Group1
    renderer->addBlock(
        _box_length__px/2,
        _box_length__px/2,
        Coordinate(xCenter -_x_column_width/2, _y_offset + _box_length__px/4),
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
        Coordinate(xCenter +_x_column_width/2, _y_offset + _box_length__px/4),
        _the_color_infos[_colors[2].second].rgba
    );

    
    

    renderer->renderText(
        xCenter - _x_column_width/2 + _box_length__px,
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
        xCenter + _x_column_width/2 + _box_length__px,
        _y_offset,
        "Group 2 Unhappy",
        4
    );
*/
}