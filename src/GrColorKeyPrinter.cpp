#include "GrColorKeyPrinter.h"
#include <algorithm>

using namespace std;

void GrColorKeyPrinter::print (Renderer* renderer)
{ 
    renderer->setTextFormats(
        textColor, 
        textBackgroundColor, 
        _label_letter.letterHeight()
    );

    // Create vector of labels and corresponding colors. Put in order of groupIds.
    // While creating vector, keep track of longest string for later use in column size.
    vector<int> groupIds;
    for (auto itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        groupIds.push_back(itr->first);
    }
    sort(groupIds.begin(), groupIds.end());

    vector<pair<Color, string>> color_and_label;
    int longestString = 0;

    for (int& groupId : groupIds)
    {
        BaseColor baseColor = _colors[groupId];
        for (auto mood : _moods)
        {
            string label = "Group: " + to_string(groupId);
            if (mood != Mood::neutral)
            {
                label = label + " " + _colorrs_map[baseColor][mood]._mood_name;
            }

            color_and_label.push_back({_colorrs_map[baseColor][mood]._color, label});

            int textWidth = (int)(label.length() *
                renderer->widthMultiplier() *
                _label_letter.letterHeight());

            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
        }
    }

    int columnWidth = longestString + _box_length__px + _box_spacer__px + _column_border__px;
    int label_top_y__px = _top_center_y__px;
    int box_top_y__px = _top_center_y__px + ( (_label_letter.letterHeight() - _box_length__px)/2 );
    int first_col_left__px = _top_center_x__px - ((double)columnWidth * color_and_label.size()/2);
    int counter = 0;
    for (auto& key : color_and_label)
    {
        string label = key.second;
        int labelWidth =  
            (int)(label.length() *
            renderer->widthMultiplier() *
            _label_letter.letterHeight());

        // left edge of colored box
        int box_left_x__px =
            first_col_left__px +
            (counter * columnWidth) +
            (0.5 * columnWidth) -
            ((labelWidth + _box_length__px + _box_spacer__px )/2);

        renderer->addBlock(
            _box_length__px,
            _box_length__px,
            Coordinate(box_left_x__px, box_top_y__px),
            _the_color_rgba[key.first]
        );

        // left edge of label
        int label_left_x__px = box_left_x__px + _box_length__px + _box_spacer__px;
        
        renderer->renderText(
            label_left_x__px,
            label_top_y__px,
            label,
            _label_letter.letterHeight(),
            _label_letter.widthMultiplier(),
            4
        );
        counter += 1;
    }
}

void GrColorKeyPrinter::setTopCenter (int xPx, int yPx) {
        _top_center_x__px = xPx;
        _top_center_y__px = yPx;
}

void GrColorKeyPrinter::setCharWidthMultiplier (double multiplier) {
    _char_width_multiplier = multiplier;
}

int GrColorKeyPrinter::sizeXPx ()
{
    int longestString = 0;

    for (unordered_map<int, BaseColor>::iterator itr = _colors.begin(); itr != _colors.end(); ++itr)
    {
        int groupId = itr->first;
        BaseColor baseColor = itr->second;
        for (auto mood : _moods)
        {
            string text = "Group: " + to_string(groupId);
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

int GrColorKeyPrinter::sizeYPx ()
{
    return _label_letter.getHeightIncLSpace();
}