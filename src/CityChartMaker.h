#ifndef CITY_CHART_MAKER_H
#define CITY_CHART_MAKER_H

#include "ChartMaker.h"
#include "Letter.h"

class CityChartMaker : public ChartMaker
{

public:

    void setTitle (Letter letter, std::string title)
    {
        _title_letter = letter;
        _title_string = title;
    }
    void setTitleTopCenter (int topCenterXPx, int topCenterYPx)
    {
        _title_top_center_x__px = topCenterXPx;
        _title_top_center_y__px = topCenterYPx;
    }

    void setColorKey (
        Letter letter,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods
    )
    {
        _key_letter = letter;
        _key_colors = colors;
        _key_moods = moods;
    }

    void setColorKeyTopCenter (int topCenterXPx, int topCenterYPx)
    {
        _key_top_center_x__px = topCenterXPx;
        _key_top_center_y__px = topCenterYPx;
    }

private:
    
    Letter      _title_letter;
    std::string _title_string;
    int         _title_top_center_x__px;
    int         _title_top_center_y__px;

    Letter                             _key_letter;
    std::unordered_map<int, BaseColor> _key_colors;
    std::set<Mood>                     _key_moods;
    int                                _key_top_center_x__px;
    int                                _key_top_center_y__px;



};

#endif