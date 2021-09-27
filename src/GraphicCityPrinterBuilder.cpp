#include "GraphicCityPrinterBuilder.h"

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addRenderer (
    Renderer* renderer
)
{
    _renderer = renderer;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addCoordinateToHouseMap (
    std::map<Coordinate,House*> map
)
{
    _coordinate_to_house_map = map;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addCrossHairsCoordinate (
    Coordinate coord
)
{
    _cross_hairs_x = coord.getX();
    _cross_hairs_y = coord.getY();
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addResidentColors (std::set<Color> resColors)
{
    _resident_colors = resColors;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addCellSize (int cellSize)
{
    _cell_size = cellSize;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addXAxisTickSpacing (
    int tickSpacing
)
{
    _tick_spacing_x = tickSpacing;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addYAxisTickSpacing (
    int tickSpacing
)
{
    _tick_spacing_y = tickSpacing;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addAxesWidthInPixels (
    int axesWidth
)
{
    _axes_width__px = axesWidth;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addXAxisLabelSpacing (
    int labelSpacing
)
{
    _label_spacing_x = labelSpacing;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addYAxisLabelSpacing (
    int labelSpacing
)
{
    _label_spacing_y = labelSpacing;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addMinimumXValueForHouse (
    int minXHouse
)
{
    _min_house_x = minXHouse;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addMaximumXValueForHouse (
    int maxXHouse
)
{
    _max_house_x = maxXHouse;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addMinimumYValueForHouse (
    int minYHouse
)
{
    _min_house_y = minYHouse;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addMaximumYValueForHouse (
    int maxYHouse
)
{
    _max_house_y = maxYHouse;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addXAxisOffsetInPixels (
    int xAxisOffset
)
{
    _x_axis_offset = xAxisOffset;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addYAxisOffsetInPixels (
    int yAxisOffset
)
{
    _y_axis_offset = yAxisOffset;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addXAxisOverrunInPixels (
    int xAxisOverrun
)
{
    _x_axis_overrun = xAxisOverrun;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addYAxisOverrunInPixels (
    int yAxisOverrun
)
{
    _y_axis_overrun = yAxisOverrun;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addFontSizeForTickLabels (
    int fontSize
)
{
    _font_size_tick_labels = fontSize;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addFontSizeForKeyLabels (
    int fontSize
)
{
    _font_size_key_labels = fontSize;
}

GraphicCityPrinterBuilder GraphicCityPrinterBuilder::addFontSizeForTitle (
    int fontSize
)
{
    _font_size_title = fontSize;
}