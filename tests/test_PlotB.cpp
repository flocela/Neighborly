#include "catch.hpp"
/*#include "../src/PlotB.h"

TEST_CASE("PlotB:: create basic PlotB")
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

    PlotB plotB(
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
    REQUIRE(topLeftXPx == plotB.getTopLeftXPx());
    REQUIRE(topLeftYPx == plotB.getTopLeftYPx());
    REQUIRE(xSpacePx == plotB.getXSpacePx());
    REQUIRE(ySpacePx == plotB.getYSpacePx());

    // Need unit sizes and plot sizes to test if increasing the unit sizes would
    // make the plot exceed its allowable space
    // PlotB uses the same unit size in both directions.
    int unitSizeXPx = plotB.getXUnitSizePx();
    int unitSizeYPx = plotB.getYUnitSizePx();
    int plotSizeX   = plotB.sizeXPx();
    int plotSizeY   = plotB.sizeYPx();

    REQUIRE( unitSizeXPx == unitSizeYPx );

    REQUIRE( xSpacePx > plotB.sizeXPx());
    REQUIRE( ySpacePx > plotB.sizeYPx());

    // PlotB uses the same unit size in both directions.
    // Increasing the unit size will make one or both of the
    // axes too long to fit in XYSpace.
    // For instance increasing the unit size by one will increase the plotSizeY
    // by 1 x (maxY - minY) which may be over the allowable size ySpacePx.
    int increasedXSize = plotSizeX + ( (maxX-minX + startOffsetMultiplier + endOffsetMultiplier) * 1);
    int increasedYSize = plotSizeY + ( (maxY-minY + startOffsetMultiplier + endOffsetMultiplier) * 1);
    int isWithinAllowable = (increasedXSize <= xSpacePx) && (increasedYSize <= ySpacePx);
    REQUIRE( isWithinAllowable == false);
}

TEST_CASE("plotB:: setTopLeft")
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

    PlotB plotB(
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
    xSpacePx = plotB.getXSpacePx();
    ySpacePx = plotB.getYSpacePx();
    int unitSizeXPx = plotB.getXUnitSizePx();
    int unitSizeYPx = plotB.getYUnitSizePx();
    int dotSizePx = plotB.getDotSizePx();

    // setTopLeft
    int newXPx = 100;
    int newYPx = 100;
    plotB.setPlot(newXPx, newYPx, xSpacePx, ySpacePx);

    REQUIRE(newXPx == plotB.getTopLeftXPx());
    REQUIRE(newYPx == plotB.getTopLeftYPx());
    REQUIRE(xSpacePx == plotB.getXSpacePx());
    REQUIRE(ySpacePx == plotB.getYSpacePx());
    REQUIRE(unitSizeXPx == plotB.getXUnitSizePx());
    REQUIRE(unitSizeYPx == plotB.getYUnitSizePx());
    REQUIRE(dotSizePx == plotB.getDotSizePx());
}

TEST_CASE("PlotB:: change available space")
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

    PlotB plotB(
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

    // before setXYSpace
    xSpacePx = plotB.getXSpacePx();
    ySpacePx = plotB.getYSpacePx();

    // change the available space
    int newSpaceXPx = 500;
    int newSpaceYPx = 250;
    plotB.setPlot(topLeftXPx, topLeftYPx, newSpaceXPx, newSpaceYPx);

    int unitSizeXPx = plotB.getXUnitSizePx();
    int unitSizeYPx = plotB.getYUnitSizePx();
    int dotSizePx = plotB.getDotSizePx();
    int sizeXPx = plotB.sizeXPx();
    int sizeYPx = plotB.sizeYPx();
    REQUIRE(topLeftXPx == plotB.getTopLeftXPx());
    REQUIRE(topLeftYPx == plotB.getTopLeftYPx());
    REQUIRE(newSpaceXPx == plotB.getXSpacePx());
    REQUIRE(newSpaceYPx == plotB.getYSpacePx());

    REQUIRE( xSpacePx > plotB.sizeXPx());
    REQUIRE( ySpacePx > plotB.sizeYPx());

    // PlotB uses the same unit size in both directions.
    // Increasing the unit size will make one or both of the
    // axes too long to fit in new available space.
    // For instance increasing the unit size by one will increase the plotSizeY
    // by 1 x (maxY - minY + startOffsetMultiplier + endOffsetMultiplier) which may be over the
    // allowable size ySpacePx. 
    int increasedXSize = sizeXPx + ( (maxX-minX + startOffsetMultiplier + endOffsetMultiplier) );
    int increasedYSize = sizeYPx + ( (maxY-minY + startOffsetMultiplier + endOffsetMultiplier) );
    int isWithinAllowable = (increasedXSize <= newSpaceXPx) && (increasedYSize <= newSpaceYPx);
    REQUIRE( isWithinAllowable == false);
}

*/
