#include <limits.h>
#include "gtest/gtest.h"
#include "vertexcover.h"

class Question5Test: public testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(Question5Test, Get_standalone_nodes_number_Successful) {
    int num;
    num = read_data("4 1 2 1 3 1 4");

    EXPECT_EQ(get_standalone_nodes_number(num), 0);
}

TEST_F(Question5Test, Get_standalone_nodes_number_Successful1) {
    int num;
    num = read_data("4 1 2 1 3");

    EXPECT_EQ(get_standalone_nodes_number(num), 1);
}

TEST_F(Question5Test, Get_standalone_nodes_number_Successful2) {
    int num;
    num = read_data("4");

    EXPECT_EQ(get_standalone_nodes_number(num), 4);
}

TEST_F(Question5Test, Get_standalone_nodes_number_Successful3) {
    int num;
    num = read_data("8 1 2 5 6 2 7 3 8 1 6 4 5");

    EXPECT_EQ(get_standalone_nodes_number(num), 0);
}

TEST_F(Question5Test, Get_one_link_nodes_number_Successful) {
    int num;
    num = read_data("4 1 2 3 4");

    EXPECT_EQ(get_one_link_nodes_number(num), 2);
}

TEST_F(Question5Test, Get_one_link_nodes_number_Successful1) {
    int num;
    num = read_data("4 1 2");

    EXPECT_EQ(get_one_link_nodes_number(num), 1);
}

TEST_F(Question5Test, Get_one_link_nodes_number_Successful3) {
    int num;
    num = read_data("8 1 2 5 6 2 7 3 8 1 6 4 5");

    EXPECT_EQ(get_one_link_nodes_number(num), 1);
}

TEST_F(Question5Test, Get_optimal_nodes_number_to_cover) {
    int num;
    num = read_data("4 1 2 1 3 1 4");
    print_edges(num);

    EXPECT_EQ(get_optimal_nodes_number(num), 1);
}


TEST_F(Question5Test, Get_optimal_nodes_number_to_cover1) {
    int num;
    int edges_expected[8 + 1] = {0, 1, 0, 0, 0, 0, 1, 0, 0};
    num = read_data("8 1 2 5 6 2 7 1 6 4 5");

    EXPECT_EQ(get_optimal_nodes_number(num), 2);
    EXPECT_EQ(memcmp(edges, edges_expected, sizeof(edges_expected)), 0);
}
