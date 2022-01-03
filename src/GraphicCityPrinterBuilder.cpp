#include "GraphicCityPrinterBuilder.h"

std::unique_ptr<GraphicCityPrinter> GraphicCityPrinterBuilder::build ()
{
    
    return std::make_unique<GraphicCityPrinter> (
        _renderer, 
        _coordinate_to_house_map,
        _cross_hairs_x,
        _cross_hairs_y,
        _resident_colors,
        _cell_size,
        _tick_spacing_x,
        _tick_spacing_y,
        _tick_width_px,
        _axes_width_px,
        _label_spacing_x,
        _label_spacing_y,
        _min_house_x,
        _max_house_x,
        _min_house_y,
        _max_house_y,
        _x_axis_offset,
        _y_axis_offset,
        _x_axis_overrun,
        _y_axis_overrun,
        _font_size_tick_labels,
        _font_size_key_labels,
        _font_size_title
    );
    
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addRenderer (
    Renderer* renderer
)
{
    _renderer = renderer;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addCoordinateToHouseMap (
    std::map<Coordinate,House*> map
)
{
    _coordinate_to_house_map = map;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addCrossHairsCoordinate (
    Coordinate coord
)
{
    _cross_hairs_x = coord.getX();
    _cross_hairs_y = coord.getY();
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addResidentColors (std::set<Color> resColors)
{
    _resident_colors = resColors;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addCellSize (int cellSize)
{
    _cell_size = cellSize;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addXAxisTickSpacing (
    int tickSpacing
)
{
    _tick_spacing_x = tickSpacing;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addYAxisTickSpacing (
    int tickSpacing
)
{
    _tick_spacing_y = tickSpacing;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addWidthOfTicksInPixels (
    int tickWidthPx
)
{
    _tick_width_px = tickWidthPx;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addAxesWidthInPixels (
    int axesWidth
)
{
    _axes_width_px = axesWidth;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addXAxisLabelSpacing (
    int labelSpacing
)
{
    _label_spacing_x = labelSpacing;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addYAxisLabelSpacing (
    int labelSpacing
)
{
    _label_spacing_y = labelSpacing;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addMinimumXValueForHouse (
    int minXHouse
)
{
    _min_house_x = minXHouse;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addMaximumXValueForHouse (
    int maxXHouse
)
{
    _max_house_x = maxXHouse;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addMinimumYValueForHouse (
    int minYHouse
)
{
    _min_house_y = minYHouse;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addMaximumYValueForHouse (
    int maxYHouse
)
{
    _max_house_y = maxYHouse;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addXAxisOffsetInPixels (
    int xAxisOffset
)
{
    _x_axis_offset = xAxisOffset;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addYAxisOffsetInPixels (
    int yAxisOffset
)
{
    _y_axis_offset = yAxisOffset;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addXAxisOverrunInPixels (
    int xAxisOverrun
)
{
    _x_axis_overrun = xAxisOverrun;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addYAxisOverrunInPixels (
    int yAxisOverrun
)
{
    _y_axis_overrun = yAxisOverrun;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addFontSizeForTickLabels (
    int fontSize
)
{
    _font_size_tick_labels = fontSize;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addFontSizeForKeyLabels (
    int fontSize
)
{
    _font_size_key_labels = fontSize;
    return *this;
}

GraphicCityPrinterBuilder& GraphicCityPrinterBuilder::addFontSizeForTitle (
    int fontSize
)
{
    _font_size_title = fontSize;
    return *this;
}