#ifndef GRAPHIC_DIVERSITY_PRINTER_H
#define GRAPHIC_DIVERSITY_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include "XAxisUtility.h"
#include "YDownAxisUtility.h"
#include <memory>
#include "PixelConverter.h"

// Takes in a Renderer* and necessary settings to draw the diversity chart.

// The x and y axes cross at the _chart_origin.
// Allow 300 pixels to the left of x-axis for the axis labels and
// the chart's key.
// Allow 100 pixels above the y axis for the y-axis labels and the chart title.
class GraphicDiversityPrinter
{
    public:
        GraphicDiversityPrinter (
            Renderer* renderer,
            std::set<Color> resColors,
            int verticalSpacePx,
            int horizontalSpacePx,
            int crossHairsX,
            int crossHairsY,
            int numOfRuns,
            int residentBlockPx,
            int residentBlockBorderPx,
            int blockSpacing_Px,
            int runSpacingPx,
            int tickSpacingX,
            int tickSpacingY,
            int tickWidthPx,
            int axesWidthPx,
            int labelSpacingX,
            int labelSpacingY,
            // horizontal space between y-axis and first run in pixels.
            int xAxisOffsetPx,
            // vertical space between x-axis and first y value.
            int yAxisOffsetPx,
            // extra length of x-axis after last run in pixels.
            int xAxisOverrunPx,
            // extra length of y-axis above greatest diversity in pixels.
            int yAxisOverrunPx,
            int fontSizeTickLabels,
            int fontSizeKeyLabels,
            int fontSizeTitle
        );

        void printDiversity (std::map<Resident*, int> resident2like, std::map<Resident*, int> resident2diff);
    
    private:
        std::string _main_title = "Resident Diversity";
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
        

        // Axes
        std::unique_ptr<XAxisUtility> _x_axis_utility;
        std::unique_ptr<YDownAxisUtility> _y_axis_utility;

        // _x_blocks and _y_blocks hold the axes lines and the ticks on the lines.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<SDL_Rect> _y_blocks = {};

        // _x_blocks and _y_blocks hold the numerical labels on the axis ticks.
        std::vector<TextRect> _x_texts = {};
        std::vector<TextRect> _y_texts = {};

        bool _chart_base_printed = false;

        int count = 0;

        void addXAxis ();
        void addYAxis ();
        void addTitle();
        void printLegend ();

        // Initialize the blocks and texts that are used by the renderer to render
        // the axes' lines, ticks, and labels
        void initXAxisBlocks ();
        void initYAxisBlocks ();

};

#endif