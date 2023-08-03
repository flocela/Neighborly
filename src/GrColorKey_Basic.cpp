#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "GrColorKey_Basic.h"

using namespace std;

GrColorKey_Basic::GrColorKey_Basic (
    int topCenterXPx,
    int topCenterYPx,
    Letter labelLetter,
    const std::unordered_map<int, BaseColor>& colors,
    std::set<Mood> moods,
    std::vector<uint8_t> textColor,
    std::vector<uint8_t> textBackgroundColor
): _top_center_x__px{topCenterXPx},
   _top_center_y__px{topCenterYPx},
   _label_letter{labelLetter},
   _b_color_per_groupId{colors},
   _moods{moods},
   _box_length__px{_label_letter.letterHeight()/2},
   _text_color{textColor},
   _text_background_color{textBackgroundColor}
{
    setAttributes();
}

GrColorKey_Basic::GrColorKey_Basic (
    Letter labelLetter,
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods
): _label_letter{labelLetter},
   _b_color_per_groupId{colors},
   _moods{moods},
   _box_length__px{_label_letter.letterHeight()/2}
{
   setAttributes(); 
}

void GrColorKey_Basic::print (Renderer* renderer) const
{   
    // Prints each color and corresponding label in _label_per_color.
    int num_of_columns = _label_per_color.size();
    int top_of_label_y__px = _top_center_y__px;
    int top_of_box_y__px = _top_center_y__px + _label_letter.letterHeight()/2 - _box_length__px/2;
    int first_col_left__px = _top_center_x__px - (double)_column_width * num_of_columns/2;

    // Total number of columns is _label_per_color.size().
    int column_index = 0;
    for (auto& pair : _label_per_color)
    {  
        string label = pair.second;
        int labelWidth =  
            (int)(label.length() *
            _label_letter.widthMultiplier() *
            _label_letter.letterHeight());

        // left edge of colored box
        int box_left_x__px =
            first_col_left__px +
            (column_index * _column_width) +
            (0.5 * _column_width) -
            ((labelWidth + _box_length__px + _box_spacer__px )/2);

        renderer->fillBlock(
            _box_length__px,
            _box_length__px,
            Coordinate(box_left_x__px, top_of_box_y__px),
            _the_color_rgba[pair.first]
        );

        // left edge of label
        int label_left_x__px = box_left_x__px + _box_length__px + _box_spacer__px;
        
        renderer->renderText(
            label_left_x__px,
            top_of_label_y__px,
            label,
            _label_letter.letterHeight(),
            _label_letter.widthMultiplier(),
            _text_color,
            _text_background_color,
            4
        );
        column_index += 1;
    }
}

int GrColorKey_Basic::sizeXPx () const
{
    return _b_color_per_groupId.size() * _moods.size() * _column_width;
}

int GrColorKey_Basic::sizeYPx () const
{
    return _label_letter.getHeightIncLSpace();
}


void GrColorKey_Basic::setTextBackgroundColor (vector<uint8_t> color)
{
    _text_background_color = color;
}

void GrColorKey_Basic::setTextColor (vector<uint8_t>  color)
{
    _text_color = color;
}

void GrColorKey_Basic::setTopCenter (int xPx, int yPx) {
    _top_center_x__px = xPx;
    _top_center_y__px = yPx;
}

void GrColorKey_Basic::setAttributes ()
{
    // Create vector of groupIds, then sort vector.
    std::vector<int> groupIds;
    for (auto itr = _b_color_per_groupId.begin(); itr != _b_color_per_groupId.end(); ++itr)
    {
        groupIds.push_back(itr->first);
    }
    std::sort(groupIds.begin(), groupIds.end());

    // Populate the _label_per_color vector.
    // An example of a label would be "Group 1 happy".
    // Combine group ids with the moods in _moods to get all combinations of group id and moods.
    // Each base color and mood has a color associated with it, as in {12, 216, 255, 255}.

    // While creating vector, keep track of longest string for later use in column size.
    int longestString = 0;

    for (int& groupId : groupIds)
    {
        for (Mood mood : _moods)
        {
            BaseColor baseColorForGroupId = _b_color_per_groupId.at(groupId);
            
            stringstream labelStream;
            labelStream << "Group: " << to_string(groupId);;

            // If there is only one mood, then there's no need to name it.
            // Group name alone is enough.
            if (_moods.size() > 1)
            {
                labelStream << " " << mood;
            }

            string label = labelStream.str();

            _label_per_color.push_back({
                _colorrs_map[baseColorForGroupId][mood]._color,
                label});

            int textWidth = (int)(label.length() *
                _label_letter.widthMultiplier() *
                _label_letter.letterHeight());

            if (textWidth > longestString)
            {
                longestString = textWidth;
            }
        }
    }

    _column_width = longestString + _box_length__px + _box_spacer__px + 2 * _column_border__px;
}