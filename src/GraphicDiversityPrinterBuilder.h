#ifndef GRAPHIC_DIVERSITY_PRINTER_BUILDER_H
#define GRAPHIC_DIVERSITY_PRINTER_BUILDER_H

#include <memory>
#include "renderer.h"
#include "GraphicDiversityPrinter.h"

class GraphicDiversityPrinterBuilder
{
    public:
    GraphicDiversityPrinterBuilder () = default;
    GraphicDiversityPrinterBuilder (const GraphicDiversityPrinterBuilder& o) = default;
    GraphicDiversityPrinterBuilder (GraphicDiversityPrinterBuilder&& o) noexcept = default;
    GraphicDiversityPrinterBuilder& operator= (const GraphicDiversityPrinterBuilder& o) = default;
    ~GraphicDiversityPrinterBuilder () = default;

    std::unique_ptr<GraphicDiversityPrinter> build ();
    GraphicDiversityPrinterBuilder& addRenderer (Renderer* renderer);
    GraphicDiversityPrinterBuilder& addLengthOfYAxisInPx (int lengthOfYAxis);
    GraphicDiversityPrinterBuilder& addLengthOfXAxisInPx (int lengthOfXAxis);
    GraphicDiversityPrinterBuilder& addCrossHairsXInPx (int crossHairsX);
    GraphicDiversityPrinterBuilder& addCrossHairsYInPx (int crossHairsY);
    GraphicDiversityPrinterBuilder& addNumOrRuns (int numOfRuns);
    GraphicDiversityPrinterBuilder& addResidentBlockInPx (int residentBlockSize);
    GraphicDiversityPrinterBuilder& addResidentBlockBorderInPx (int residentBlockBorder);
    GraphicDiversityPrinterBuilder& addResidentBlockSpacingInPx (int residentBlockSpacing);
    GraphicDiversityPrinterBuilder& addSpacingPerRunInPx (int runSpacing);
    GraphicDiversityPrinterBuilder& addTickSpacingXInPx (int tickSpacingX);
    GraphicDiversityPrinterBuilder& addTickSpacingYInPx (int tickSpacingY);
    GraphicDiversityPrinterBuilder& addTickWidthInPx (int tickWidth);
    GraphicDiversityPrinterBuilder& addAxisWidthInPx (int axisWidth);
    GraphicDiversityPrinterBuilder& addLabelSpacingXInPx (int labelSpacingX);
    GraphicDiversityPrinterBuilder& addLabelSpacingYInPx (int labelSpacingY);
    GraphicDiversityPrinterBuilder& addXAxisOffsetInPx (int xAxisOffset);
    GraphicDiversityPrinterBuilder& addYAxisOffsetInPx (int yAxisOffset);
    GraphicDiversityPrinterBuilder& addXAxisOverrunInPx (int xAxisOverrun);
    GraphicDiversityPrinterBuilder& addYAxisOverrunInPx (int yAxisOverrun);
    GraphicDiversityPrinterBuilder& addFontSizeAxesTickLabels (int fontSizeTickLabels);
    GraphicDiversityPrinterBuilder& addFontSizeKeyLabels (int fontSizeKeyLabels);
    GraphicDiversityPrinterBuilder& addFontSizeTitle (int fontSizeTitle);

    private:
    Renderer* _renderer;
    std::map<Coordinate, House*> _coord_to_house_map;
    std::unique_ptr<PixelConverter> _pixel_converter_x;
    std::unique_ptr<PixelConverter> _pixel_converter_y;
    int _length_of_y_axis__px;
    int _length_of_x_axis__px;
    // The coordinate where x and y axes cross on the screen in pixels.
    int _cross_hairs_x__px;
    int _cross_hairs_y__px;
    // This includes sad resident colors and happy resident colors.
    std::set<Color> _res_colors;
    int _num_of_runs; 
    // colored blocks are 3 pixels wide
    int _resident_block__px;
    // colored blocks border
    int _resident_block_border__px;
    // spacing between resident blocks is 1 pixel.
    int _resident_block_spacing__px;
    // spacing between runs is 3 pixels
    int _run_spacing__px;
    // _cell_size is the spacing between ticks on the x and y axes.
    // It is determined as: 
    // for each resident type one _resident_block__px + two _block_spacing__px,
    // plus two (one per side) _resident_block_border__px,
    // plus one _block_spacing__px per resident type above one,
    // plus two (one per side) _run_spacing__px
    int _cell_size_x__px;
    // tick spacing on axes. Remember, not all cells will have ticks designating them.
    int _tick_spacing_x;
    int _tick_spacing_y;
    // tick width in pixels.
    int _tick_width__px;
    // The width of the ticks along the axes. Same for x and y axes.
    int _axes_width__px;

    // label spacing on axes.
    int _label_spacing_x;
    int _label_spacing_y;
    // the zeroeth run will not be on the y-axis. It will be offset to the right.
    int _x_axis_offset__px;
    int _y_axis_offset__px;
    // Overruns are how much farther the axis runs past the last run.
    // If the x-axis were to originally stop at the max_run__px, then instead 
    // it will stop at the value _max_run__px + _cell_size__px/2 + _x_axis_overrun__px.
    int _x_axis_overrun__px;
    int _y_axis_overrun__px;
    // pixel value for the zeroeth run.
    int _min_run__px;
    // pixel value for the last run.
    int _max_run__px;
    // titlesAtTopOffset and titlesLeftOffset is room given for titles at top
    // and left of the graph.
    int _titles_at_left_offset__px = 290; // this should be given in the constructor.
    int _titles_at_top_offset__px = 0;
    int _title_y__px = 0;
    int _dist_from_title_to_legend = 90;
    // fontSizes
    int _font_size_axes_tick_labels = 0;
    int _font_size_key = 0; 
    int _font_size_title = 0;

};
#endif