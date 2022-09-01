#include "GrColorKeyPrinter.h"
#include <algorithm>

void GrColorKeyPrinter::print (Renderer* renderer)
{ 
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

    int columnWidth = _x_space_length__px/(groups.size() * moods.size());
    std::vector<std::pair<Color, std::string>> keys;
    int longestString = 0;

    for (int gg=0; gg<(int)groups.size(); ++gg)
    {
        for (int mm=0; mm<(int)moods.size(); ++mm)
        {
            int group_id = groups[gg];
            Color color = _colors[group_id];

            std::string text;
            if (moods[mm] == "neutral")
            {
                text = "Group: " + std::to_string(group_id);
            }
            else
            {
                text = "Group: " + std::to_string(group_id) + " " + moods[mm];
            }

            int textWidth =  
                (int)(text.length() *
                renderer->widthMultiplier() *
                _title_letter.letterHeight());
            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
            keys.push_back(std::pair{_color_map[color][moods[mm]], text});
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
    return _title_letter.letterHeight();
}