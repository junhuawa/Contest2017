#include <limits.h>
#include "gtest/gtest.h"
#include "question4.h"

class Question4Test: public testing::Test {
    protected:
        virtual void SetUp() {
            init();
        }

        virtual void TearDown() {
        }
};

TEST_F(Question4Test, FindShortestRoad) {
    int tmp[4][4] = {
        {},
        {0, 0, 0, 692},
        {0, 0, 0, 179},
        {0, 692, 179, 0}
    };
    for(int i=1; i<3+1; i++){
        for(int j=1; j<3+1; j++){
            weight[i][j] = tmp[i][j];
        }
    }

    printf("w[1][3]: %d\n", weight[1][3]);

    display_weight(3);
    EXPECT_EQ(get_shortest_total_length(3), 179);
}

TEST_F(Question4Test, FindShortestRoad1) {
    int tmp[5+1][5+1] = {
        {},
        {0, 0, 102, 182, 0, 390},
        {0, 102, 0, 123, 168, 298},
        {0, 182, 123, 0, 135, 214},
        {0, 0, 168, 135, 0, 52},
        {0, 390, 298, 214, 52, 0}
    };
    for(int i=1; i<5+1; i++){
        for(int j=1; j<5+1; j++){
            weight[i][j] = tmp[i][j];
        }
    }

    display_weight(5);
    EXPECT_EQ(get_shortest_total_length(5), 289);
}

TEST_F(Question4Test, FindShortestRoad2) {
    int tmp[7+1][7+1] = {
        {},
        {0,  0,  2,  4,  1,  1000,  1000,  1000},
        {0,  2,  0,  1000,  3,  10, 1000,  1000},
        {0,  4,  1000,  0,  2,  1000,  5,  1000},
        {0,  1,  3,  2,  0,  7,  8,  4},
        {0,  1000,  10, 1000,  7,  0,  1000,  6},
        {0,  1000,  1000,  5,  8,  1000,  0,  1}, 
        {0,  1000,  1000,  1000,  4,  6,  1,  0}
    };
    for(int i=1; i<7+1; i++){
        for(int j=1; j<7+1; j++){
            weight[i][j] = tmp[i][j];
        }
    }

    display_weight(7);
    EXPECT_EQ(get_shortest_total_length(7), 16);
}
