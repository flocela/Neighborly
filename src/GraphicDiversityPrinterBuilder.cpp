#include "GraphicDiversityPrinterBuilder.h"

std::unique_ptr<GraphicDiversityPrinter> GraphicDiversityPrinterBuilder::build () 
{
    return std::make_unique <GraphicDiversityPrinter> (
        _renderer,
        _res_colors,
        _length_of_y_axis__px,
        _length_of_x_axis__px,
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _num_of_runs,
        _resident_block__px,
        _resident_block_border__px,
        _resident_block_spacing__px,
        _run_spacing__px,
        _tick_spacing_x,
        _tick_spacing_y,
        _tick_width__px,
        _axes_width__px,
        _label_spacing_x,
        _label_spacing_y,
        _x_axis_offset__px,
        _y_axis_offset__px,
        _x_axis_overrun__px,
        _y_axis_overrun__px,
        _font_size_axes_tick_labels,
        _font_size_key,
        _font_size_title
    );
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addRenderer (
    Renderer* renderer
)
{
    _renderer = renderer;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addLengthOfYAxisInPx (
    int lengthOfYAxis
)
{
    _length_of_y_axis__px = lengthOfYAxis;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addLengthOfXAxisInPx (int lengthOfXAxis) {
    _length_of_x_axis__px = lengthOfXAxis;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addCrossHairsXInPx (int crossHairsX) {
    _cross_hairs_x__px = crossHairsX;
    return *this;

}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addCrossHairsYInPx (int crossHairsY) {
    _cross_hairs_y__px = crossHairsY;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addNumOrRuns (int numOfRuns) {
    _num_of_runs = numOfRuns;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addResidentBlockInPx (int residentBlockSize) {
    _resident_block__px = residentBlockSize;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addResidentBlockBorderInPx (int residentBlockBorder) {
    _resident_block_border__px = residentBlockBorder;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addResidentBlockSpacingInPx (int residentBlockSpacing) {
    _resident_block_spacing__px = residentBlockSpacing;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addSpacingPerRunInPx (int runSpacing) {
    _run_spacing__px = runSpacing;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addTickSpacingXInPx (int tickSpacingX) {
    _tick_spacing_x = tickSpacingX;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addTickSpacingYInPx (int tickSpacingY) {
    _tick_spacing_y = tickSpacingY;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addTickWidthInPx (int tickWidth) {
    _tick_width__px = tickWidth;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addAxisWidthInPx (int axisWidth) {
    _axes_width__px = axisWidth;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addLabelSpacingXInPx (int labelSpacingX) {
    _label_spacing_x = labelSpacingX;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addLabelSpacingYInPx (int labelSpacingY) {
    _label_spacing_y = labelSpacingY;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addXAxisOffsetInPx (int xAxisOffset) {
    _x_axis_offset__px = xAxisOffset;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addYAxisOffsetInPx (int yAxisOffset) {
    _y_axis_offset__px = yAxisOffset;
    return *this;
}

GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addXAxisOverrunInPx (int xAxisOverrun) {
    _x_axis_overrun__px = xAxisOverrun;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addYAxisOverrunInPx (int yAxisOverrun) {
    _y_axis_overrun__px = yAxisOverrun;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addFontSizeAxesTickLabels (int fontSizeTickLabels) {
    _font_size_axes_tick_labels = fontSizeTickLabels;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addFontSizeKeyLabels (int fontSizeKeyLabels) {
    _font_size_key = fontSizeKeyLabels;
    return *this;
}
GraphicDiversityPrinterBuilder& GraphicDiversityPrinterBuilder::addFontSizeTitle (int fontSizeTitle) {
    _font_size_title = fontSizeTitle;
    return *this;
}