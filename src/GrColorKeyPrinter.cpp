#include "GrColorKeyPrinter.h"
#include <algorithm>

void GrColorKeyPrinter::print (Renderer* renderer)
{ 
    renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _label_letter.letterHeight()
    );

    std::vector<int> groupIds;
    for (std::unordered_map<int, BaseColor>::iterator itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        groupIds.push_back(itr->first);
    }

    std::sort(groupIds.begin(), groupIds.end());

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
                _label_letter.letterHeight());
            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
            keys.push_back({_colorrs_map[baseColor][mood]._my_color, text});
        }
    }

    int columnWidth = longestString + _box_length__px + _box_spacer__px + _column_border__px;

    int left = _top_center_x__px- ((double)columnWidth * keys.size()/2);
    int counter = 0;
    for (auto& key : keys)
    {
        std::string name = key.second;
        int textWidth =  
            (int)(name.length() *
            renderer->widthMultiplier() *
            _label_letter.letterHeight());

        // left edge of colored box
        int boxX =
            left +
            (counter * columnWidth) +
            (0.5 * columnWidth) -
            ((textWidth + _box_length__px + _box_spacer__px )/2);

        int textX = boxX + _box_length__px + _box_spacer__px;

        renderer->addBlock(
            _box_length__px,
            _box_length__px,
            Coordinate(boxX,_top_center_y__px + ((_label_letter.letterHeight() - _box_length__px)/2)),
            _the_color_rgba[key.first]
        );
        
        renderer->renderText(
            textX,
            _top_center_y__px,
            name,
            _label_letter.letterHeight(),
            _label_letter.widthMultiplier(),
            4
        );
        counter += 1;
    }
}

int GrColorKeyPrinter::sizeXPx ()
{
    int longestString = 0;

    for (std::unordered_map<int, BaseColor>::iterator itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        int groupId = itr->first;
        BaseColor baseColor = itr->second;
        for (auto mood : _moods)
        {
            std::string text = "Group: " + std::to_string(groupId);
            if (mood != Mood::neutral)
            {
                text = text + " " + _colorrs_map[baseColor][mood]._mood_name;
            }

            int textWidth =  
                (int)(text.length() *
                _char_width_multiplier *
                _label_letter.letterHeight());
            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
        }
    }

    int columnWidth = longestString + _box_length__px + _box_spacer__px + _column_border__px;
    return _colors.size() * _moods.size() * columnWidth;
}