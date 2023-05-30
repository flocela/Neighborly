#include "catch.hpp"
#include "../src/PlotA.h"


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

    // unitSizeXPx and unitSizeYPx must both be even or both be odd
    REQUIRE( (unitSizeXPx%2) == (unitSizeYPx%2) );

    // dot's even/oddness must match unit sizes' even/oddness
    REQUIRE ( unitSizeXPx%2 == plotA.getDotSizePx()%2);

    // plot should take up a large part of the available space given
    REQUIRE( (0.65 * xSpacePx) < plotA.sizeXPx());
    REQUIRE( xSpacePx > plotA.sizeXPx());
    REQUIRE( (0.65 * ySpacePx) < plotA.sizeYPx());
    REQUIRE( ySpacePx > plotA.sizeYPx());

    // increasing one or both of the unitSizes will make one or both of the
    // axes too long to fit in XYSpace.
    // for instance increasing the unitSizeXPx by one will increase the plotSizeY
    // by 1 x (maxY - minY) which would be over the allowable size ySpacePx
    // since the unit sizes' odd/evenness has to match, an increase of one in the
    // y unit size would result in an increase by one in the x unit size.
    int increasedXSize = plotSizeX + ( (maxX-minX) * 1);
    int increasedYSize = plotSizeY + ( (maxY-minY) * 1);
    int isWithinAllowable = (increasedXSize <= xSpacePx) && (increasedYSize <= ySpacePx);
    REQUIRE( isWithinAllowable == false);
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

    // setTopLeft
    int newXPx = 100;
    int newYPx = 100;
    plotA.setTopLeft(newXPx, newYPx);

    REQUIRE(newXPx == plotA.getTopLeftXPx());
    REQUIRE(newYPx == plotA.getTopLeftYPx());
    REQUIRE(xSpacePx == plotA.getXSpacePx());
    REQUIRE(ySpacePx == plotA.getYSpacePx());
    REQUIRE(unitSizeXPx == plotA.getXUnitSizePx());
    REQUIRE(unitSizeYPx == plotA.getYUnitSizePx());
    REQUIRE(dotSizePx == plotA.getDotSizePx());
}

TEST_CASE("PlotA:: setXYSpacePx")
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

    // setXYSpacePx
    int newXPx = 500;
    int newYPx = 250;
    plotA.setXYSpacePx(newXPx, newYPx);

    int unitSizeXPx = plotA.getXUnitSizePx();
    int unitSizeYPx = plotA.getYUnitSizePx();
    int dotSizePx = plotA.getDotSizePx();
    int sizeXPx = plotA.sizeXPx();
    int sizeYPx = plotA.sizeYPx();

    REQUIRE(topLeftXPx == plotA.getTopLeftXPx());
    REQUIRE(topLeftYPx == plotA.getTopLeftYPx());
    REQUIRE(newXPx == plotA.getXSpacePx());
    REQUIRE(newYPx == plotA.getYSpacePx());

    // unitSizeXPx and unitSizeYPx must both be even or both be odd
    REQUIRE( (unitSizeXPx%2) == (unitSizeYPx%2) );
    
    // dot's even/oddness must match unit sizes' even/oddness
    REQUIRE ( unitSizeXPx%2 == plotA.getDotSizePx()%2);

    // plot should take up a large part of the available space given
    REQUIRE( (0.65 * newXPx) < plotA.sizeXPx());
    REQUIRE( xSpacePx > plotA.sizeXPx());
    REQUIRE( (0.65 * ySpacePx) < plotA.sizeYPx());
    REQUIRE( ySpacePx > plotA.sizeYPx());

    // increasing one or both of the unitSizes will make one or both of the
    // axes too long to fit in XYSpace.
    // for instance increasing the unitSizeXPx by one will increase the plotSizeY
    // by 1 x (maxY - minY) which would be over the allowable size ySpacePx
    // since the unit sizes' odd/evenness has to match, an increase of one in the
    // y unit size would result in an increase by one in the x unit size.
    int increasedXSize = sizeXPx + ( (maxX-minX) * 1);
    int increasedYSize = sizeYPx + ( (maxY-minY) * 1);
    int isWithinAllowable = (increasedXSize <= newXPx) && (increasedYSize <= newYPx);
    REQUIRE( isWithinAllowable == false);
}


