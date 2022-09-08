#include "GrColorKeyPrinter.h"
#include <algorithm>

void GrColorKeyPrinter::print (Renderer* renderer)
{ 
    renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _title_letter.letterHeight()
    );

    std::vector<int> groupIds;
    for (std::unordered_map<int, BaseColor>::iterator itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        groupIds.push_back(itr->first);
    }

    std::sort(groupIds.begin(), groupIds.end());

    int columnWidth = _x_space_length__px/(groupIds.size() * _moods.size());
    std::vector<std::pair<Color, std::string>> keys;
    int longestString = 0;

    for (int& groupId : groupIds)
    {
        BaseColor baseColor = _colors[groupId];
        for (auto mood : _moods)
        {
            std::string text = "Group: " + std::to_string(groupId);
            if (mood != Mood::neutral)
            {
                text = text + " " + _colorrs_map[baseColor][mood]._mood_name;
            }

            int textWidth =  
                (int)(text.length() *
                renderer->widthMultiplier() *
                _title_letter.letterHeight());
            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
            keys.push_back({_colorrs_map[baseColor][mood]._my_color, text});
        }
    }

    // possibly make column widths smaller
    if ( (longestString + _box_length__px + _box_spacer__px + 50) * (int)keys.size() < _x_space_length__px )
    {
        columnWidth = longestString+ _box_length__px + _box_spacer__px + 50;
    }

    int left = _x_offset + (_x_space_length__px/2) - (columnWidth * keys.size()/2);

    int counter = 1;
    for (auto& key : keys)
    {
        std::string name = key.second;
        int textWidth =  
            (int)(name.length() *
            renderer->widthMultiplier() *
            _title_letter.letterHeight());

        // left edge of colored box
        int boxX =
            left +
            (counter * columnWidth/2) - 
            ((textWidth + _box_length__px + _box_spacer__px )/2);

        int textX = boxX + _box_length__px + _box_spacer__px;

        renderer->addBlock(
            _box_length__px/2,
            _box_length__px/2,
            Coordinate(boxX,_y_offset + _box_length__px/4),
            _the_color_rgba[key.first]
        );
        
        renderer->renderText(
            textX,
            _y_offset,
            name,
            4
        );
        counter = counter + 2;
    }
}

 int GrColorKeyPrinter::getHeightPx ()
{
    return _title_letter.getHeightIncLSpace();
}