#include "catch.hpp"
/*#include "../src/PlotA.h"

using namespace std;

TEST_CASE("PlotA:: create basic PlotA")
{
    int topLeftXPx = 0;
    int topLeftYPx = 0;
    int minX = 0;
    int maxX = 100;
    int minY = 0;
    int maxY = 100;
    int xSpacePx = 1000;
    int ySpacePx = 500;
    
    int minUnitSize = 3;
    int startOffsetMultiplier = 1;
    int endOffsetMultiplier   = 1;

    AxisFormat x_af = AxisFormat{};
    AxisFormat y_af = AxisFormat{};
    PlotFormat pFormat{
        x_af,
        y_af,
        Letter{},
        Letter{},
        minUnitSize,
        startOffsetMultiplier,
        endOffsetMultiplier
    };
    PlotA plotA(
        pFormat,
        topLeftXPx,
        topLeftYPx,
        minX,
        maxX,
        minY,
        maxY,
        xSpacePx,
        ySpacePx
    );
    REQUIRE(topLeftXPx == plotA.getTopLeftXPx());
    REQUIRE(topLeftYPx == plotA.getTopLeftYPx());
    REQUIRE(xSpacePx == plotA.getXSpacePx());
    REQUIRE(ySpacePx == plotA.getYSpacePx());

    // need unit sizes and plot sizes to test if increasing the unit sizes would
    // make the plot exceed its allowable space
    int unitSizeXPx = plotA.getXUnitSizePx();
    int unitSizeYPx = plotA.getYUnitSizePx();
    int plotSizeX   = plotA.sizeXPx();
    int plotSizeY   = plotA.sizeYPx();

    // plot should take up a large part of the available space given
    REQUIRE( (0.65 * xSpacePx) < plotA.sizeXPx());
    REQUIRE( xSpacePx > plotA.sizeXPx());
    REQUIRE( (0.65 * ySpacePx) < plotA.sizeYPx());
    REQUIRE( ySpacePx > plotA.sizeYPx());

    // Increasing the unitSizes will make the axes too long to fit in available space.
    // For instance increasing the unit size in the y-direction by one will increase the plotSizeY
    // by 1 x (maxY - minY + startOffsetMultiplier + endOffsetMultiplier). That would
    // would make the axis larger than the allowable space, ySpacePx.
    int increasedXSize = plotSizeX + ( (maxX - minX + startOffsetMultiplier + endOffsetMultiplier) );
    int increasedYSize = plotSizeY + ( (maxY - minY + startOffsetMultiplier + endOffsetMultiplier) );
    REQUIRE(increasedXSize > xSpacePx);
    REQUIRE(increasedYSize > ySpacePx);
}

TEST_CASE("PlotA:: setTopLeft")
{
    int topLeftXPx = 0;
    int topLeftYPx = 0;
    int minX = 0;
    int maxX = 100;
    int minY = 0;
    int maxY = 100;
    int xSpacePx = 1000;
    int ySpacePx = 500;
    
    int minUnitSize = 3;
    int startOffsetMultiplier = 1;
    int endOffsetMultiplier   = 1;

    AxisFormat x_af = AxisFormat{};
    AxisFormat y_af = AxisFormat{};
    PlotFormat pFormat{
        x_af,
        y_af,
        Letter{},
        Letter{},
        minUnitSize,
        startOffsetMultiplier,
        endOffsetMultiplier
    };
    PlotA plotA(
        pFormat,
        topLeftXPx,
        topLeftYPx,
        minX,
        maxX,
        minY,
        maxY,
        xSpacePx,
        ySpacePx
    );

    // before setTopLeft
    xSpacePx = plotA.getXSpacePx();
    ySpacePx = plotA.getYSpacePx();
    int unitSizeXPx = plotA.getXUnitSizePx();
    int unitSizeYPx = plotA.getYUnitSizePx();
    int dotSizePx = plotA.getDotSizePx();

    // Changing the top left corner location doesn't change available space
    int newXPx = 100;
    int newYPx = 100;
    plotA.setPlot(newXPx, newYPx, xSpacePx, ySpacePx);
    
    REQUIRE(newXPx == plotA.getTopLeftXPx());
    REQUIRE(newYPx == plotA.getTopLeftYPx());
    REQUIRE(xSpacePx == plotA.getXSpacePx());
    REQUIRE(ySpacePx == plotA.getYSpacePx());
    REQUIRE(unitSizeXPx == plotA.getXUnitSizePx());
    REQUIRE(unitSizeYPx == plotA.getYUnitSizePx());
    REQUIRE(dotSizePx == plotA.getDotSizePx());
}

TEST_CASE("PlotA:: change available space")
{
    int topLeftXPx = 0;
    int topLeftYPx = 0;
    int minX = 0;
    int maxX = 100;
    int minY = 0;
    int maxY = 100;
    int xSpacePx = 1000;
    int ySpacePx = 500;
    
    int minUnitSize = 3;
    int startOffsetMultiplier = 1;
    int endOffsetMultiplier   = 1;

    AxisFormat x_af = AxisFormat{};
    AxisFormat y_af = AxisFormat{};
    PlotFormat pFormat{
        x_af,
        y_af,
        Letter{},
        Letter{},
        minUnitSize,
        startOffsetMultiplier,
        endOffsetMultiplier
    };
    PlotA plotA(
        pFormat,
        topLeftXPx,
        topLeftYPx,
        minX,
        maxX,
        minY,
        maxY,
        xSpacePx,
        ySpacePx
    );

    // before setXYSpacePx
    xSpacePx = plotA.getXSpacePx();
    ySpacePx = plotA.getYSpacePx();

    // Changing available space doesn't change top left corner
    int newSpaceXPx = 500;
    int newSpaceYPx = 250;
    plotA.setPlot(topLeftXPx, topLeftYPx, newSpaceXPx, newSpaceYPx);
    
    REQUIRE(topLeftXPx == plotA.getTopLeftXPx());
    REQUIRE(topLeftYPx == plotA.getTopLeftYPx());
    REQUIRE(newSpaceXPx == plotA.getXSpacePx());
    REQUIRE(newSpaceYPx == plotA.getYSpacePx());

    int unitSizeXPx = plotA.getXUnitSizePx();
    int unitSizeYPx = plotA.getYUnitSizePx();
    int dotSizePx = plotA.getDotSizePx();
    int sizeXPx = plotA.sizeXPx();
    int sizeYPx = plotA.sizeYPx();

    // Plot should take up a large part of the available space given.
    REQUIRE( (0.65 * newSpaceXPx) < plotA.sizeXPx());
    REQUIRE( xSpacePx > plotA.sizeXPx());
    REQUIRE( (0.65 * ySpacePx) < plotA.sizeYPx());
    REQUIRE( ySpacePx > plotA.sizeYPx());

    // Increasing the unitSizes will make the axes too long to fit in the new available spaces.
    // For instance increasing the unit size in the y-direction by one will increase the plotSizeY
    // by 1 x (maxY - minY + startOffsetMultiplier + endOffsetMultiplier). That would
    // would make the axis larger than the allowable space, newSpaceYPx.
    int increasedXSize = sizeXPx + (maxX - minX + startOffsetMultiplier + endOffsetMultiplier);
    int increasedYSize = sizeYPx + (maxY - minY + startOffsetMultiplier + endOffsetMultiplier);

    REQUIRE(increasedXSize > newSpaceXPx);
    REQUIRE(increasedYSize > newSpaceYPx);
}
*/

