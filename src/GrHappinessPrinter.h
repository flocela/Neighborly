#ifndef GR_HAPPINESS_PRINTER_H
#define GR_HAPPINESS_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include "XAxisL2RBottom.h"
#include "YAxisB2T.h"
#include <memory>
#include "PixelConverter.h"
#include "GrHappinessPrinterSizer.h"
#include "AxisFormat.h"
#include "Letter.h"
#include <unordered_map>

// Takes in a Renderer* and necessary settings to draw the diversity chart.

// The x and y axes cross at the _chart_origin.
// Allow 300 pixels to the left of x-axis for the axis labels and
// the chart's key.
// Allow 100 pixels above the y axis for the y-axis labels and the chart title.
// Graphic Diversity Printer
class GrHappinessPrinter
{
    public:
        GrHappinessPrinter (
            GrHappinessPrinterSizer grDivPrSizer,
            std::map<int, std::pair<Color, Color>> resColors,
            int topLeftCornerXPx,
            int topLeftCornerYPx
        );

        void print(
            std::unordered_map<int,std::vector<int>> _num_of_like_diff_per_group,
            Renderer* renderer
        );
    
    private:
        std::string _main_title = "Diversity, Average Number of Different Neighbors per Resident for Each Run";
        std::map<Coordinate, House*> _coord_to_house_map;
        // This includes sad resident colors and happy resident colors.
        std::map<int, std::pair<Color, Color>> _res_colors;
        int _top_left_corner_x__px;
        int _top_left_corner_y__px;
        int _x_given_space__px;
        int _y_given_space__px;
        AxisFormat _axis_format_X;
        AxisFormat _axis_format_Y;

        Letter _title_letter;
        int _title_x__px;
        int _title_y__px;

        int _zero_run_idx;
        int _last_run_idx;

        int _num_of_runs;

        int _length_of_y_axis__px;
        int _largest_y = 20;

        // The coordinate where x and y axes cross on the screen in pixels.
        int _cross_x__px;
        int _cross_y__px;

        std::unique_ptr<PixelConverter> _pixel_converter_x;
        std::unique_ptr<PixelConverter> _pixel_converter_y;

        // may not be able to show every coordinate, may have to show every 5th coordinate.
        // So y axis would count 0, 5, 10, 15... 
        // Datapoints from 3 to 7 would show at coordinate 5.
        int _coord_skip_y;

        int _min_tick_spacing_x;
        int _min_tick_spacing_y;
        int _maj_tick_spacing_x;
        int _maj_tick_spacing_y;

        // tick width in pixels.
        int _tick_width__px;

        // label spacing on axes.
        int _label_spacing_x;
        int _label_spacing_y;

        // Axes
        std::unique_ptr<XAxisL2RBottom> _x_axis;
        std::unique_ptr<YAxisB2T> _y_axis;

        // _x_blocks and _y_blocks hold the axes lines and the ticks on the lines.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<SDL_Rect> _y_blocks = {};

        // _x_blocks and _y_blocks hold the numerical labels on the axis ticks.
        std::vector<TextRect> _x_texts = {};
        std::vector<TextRect> _y_texts = {};

        bool _chart_base_printed = false;
        int _point_size__px = 6; // square points
        // space from crosshairs to center of first pixel is _point_size__px * off_set_multiplier
        int _offset_multiplier = 2;
        int _override_multiplier = _offset_multiplier;
        int _x_point_spacing__px; // center to center.
        int _y_point_spacing__px; 
        // if _run_skip_x == 1, then every run is printed. If _run_skip_x ==2, then every other run is printed. And so on.
        int _run_skip_x = 1; 

        int count = 0;

        void addXAxis ();
        void addYAxis ();
        void printTitle(Renderer* renderer);
        void printLegend ();

        // Initialize the blocks and texts that are used by the renderer to render
        // the axes' lines, ticks, and labels
        void initXAxisBlocks ();
        void initYAxisBlocks ();

        int calcXAxisLengthPx ();
        int calcYAxisLengthPx ();

        int calcRunModulo();
        int calcYModulo();

        int calcXCrossHairsPx ();
        int calcYCrossHairsPx ();

        int calcMajTickSpacingX ();
        int calcMinTickSpacingX ();        
        int calcMajTickSpacingY ();
        int calcMinTickSpacingY ();
        int calcLabelSpacingX ();
        int calcLabelSpacingY ();

        std::unique_ptr<PixelConverter>createPixelConverterX ();
        std::unique_ptr<PixelConverter>createPixelConverterY ();   

};

#endif