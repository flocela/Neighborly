#include "GrColorKey.h"
#include <algorithm>

using namespace std;

GrColorKey::GrColorKey (
    int topCenterXPx,
    int topCenterYPx,
    Letter labelLetter,
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods,
    SDL_Color textColor,
    SDL_Color textBackgroundColor
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

GrColorKey::GrColorKey (
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

void GrColorKey::setAttributes ()
{
    // create vector of groupIds, then order vector
    std::vector<int> groupIds;
    for (auto itr = _b_color_per_groupId.begin(); itr != _b_color_per_groupId.end(); ++itr)
    {
        groupIds.push_back(itr->first);
    }
    std::sort(groupIds.begin(), groupIds.end());

    // populate vector _label_per_color with pairs.
    // each pair is the group color and the groupId string.
    // while creating vector, keep track of longest string for later use in column size.
    int longestString = 0;

    for (int& groupId : groupIds)
    {
        BaseColor baseColor = _b_color_per_groupId[groupId];
        for (auto mood : _moods)
        {
            string label = "Group: " + to_string(groupId);
            if (mood != Mood::neutral)
            {
                label = label + " " + _colorrs_map[baseColor][mood]._mood_name;
            }

            _label_per_color.push_back({_colorrs_map[baseColor][mood]._color, label});

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


void GrColorKey::print (Renderer* renderer)
{   
    // Printed as a series of columns.
    // each column holds the groupId's colored box and the groupId's label.
    // call this box and label the group's representation.
    // each representation is centered in it's column.
    int num_of_columns = _label_per_color.size();
    int top_of_label_y__px = _top_center_y__px;
    int top_of_box_y__px = _top_center_y__px + _label_letter.letterHeight()/2 - _box_length__px/2;
    int first_col_left__px = _top_center_x__px - (double)_column_width * num_of_columns/2;

    int counter = 0;

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
            (counter * _column_width) +
            (0.5 * _column_width) -
            ((labelWidth + _box_length__px + _box_spacer__px )/2);

        renderer->addBlock(
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
        counter += 1;
    }
}

void GrColorKey::setTopCenter (int xPx, int yPx) {
    _top_center_x__px = xPx;
    _top_center_y__px = yPx;
}

int GrColorKey::sizeXPx ()
{
    return _b_color_per_groupId.size() * _moods.size() * _column_width;
}

void GrColorKey::setTextColor (SDL_Color color)
{
    _text_color = color;
}

void GrColorKey::setTextBackgroundColor (SDL_Color color)
{
    _text_background_color = color;
}

int GrColorKey::sizeYPx ()
{
    return _label_letter.getHeightIncLSpace();
}