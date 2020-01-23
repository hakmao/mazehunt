//
// Created by Johannes Flieger on 14/01/2020.
//

//
// Created by Johannes Flieger on 02/01/2020.
//
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

//#include <memory>
//#include "grid.h"
#include "grid_tests.h"

TEST_CASE("Create Grid objects from vectors of States")
{
    Grid grid1(grid_tests::sample_grid_1);
    Grid grid2(grid_tests::sample_grid_2);

    SECTION("Check rows and columns")
    {
        CHECK(grid1.rows() == grid_tests::sample_grid_1_rows);
        CHECK(grid1.cols() == grid_tests::sample_grid_1_cols);
        CHECK(grid1.size() == grid_tests::sample_grid_1_size);
    }

    SECTION("Check valid cell positions")
    {
        Cell myCell00{ 0, 0 };
        Cell myCell23{ 2, 3 };
        Cell myCell210{ 2, 10 };
        Cell myCell54{ 5, 4 };
        Cell myCell102{ 10, 2 };
        Cell myCell_210{ -2, 10 };
        Cell myCell10_2{ 10, -2 };
        Cell myCell2_3{ 2, -3 };

        CHECK(grid1.is_on_grid(myCell00));
        CHECK(grid1.is_on_grid(myCell23));
        CHECK_FALSE(grid1.is_on_grid(myCell210));
        CHECK(grid1.is_on_grid(myCell54));
        CHECK_FALSE(grid1.is_on_grid(myCell102));
        CHECK_FALSE(grid1.is_on_grid(myCell_210));
        CHECK_FALSE(grid1.is_on_grid(myCell10_2));
        CHECK_FALSE(grid1.is_on_grid(myCell2_3));
    }

    SECTION("Equality")
    {
        CHECK(grid1 == grid1); // Sanity check
        CHECK_FALSE(grid1 == grid2);
    }
}
TEST_CASE("Write and read grid files")
{
    Grid grid1(grid_tests::sample_grid_1);

    SECTION("Write to file")
    {
        CHECK(grid1.to_file(grid_tests::testfile));
    }
    SECTION("Read from file")
    {
        Grid grid2;
        CHECK( grid2.from_file(grid_tests::testfile));
        CHECK( grid1 == grid2);
    }
}

