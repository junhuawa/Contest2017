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
    //print_edges(num);

    EXPECT_EQ(get_optimal_nodes_number(num), 1);
}


TEST_F(Question5Test, Get_optimal_nodes_number_to_cover1) {
    int num;
    int edges_expected[8 + 1] = {0, 1, 0, 0, 0, 0, 1, 0, 0};
    num = read_data("8 1 2 5 6 2 7 1 6 4 5");

    EXPECT_EQ(get_optimal_nodes_number(num), 2);
    EXPECT_EQ(memcmp(edges, edges_expected, sizeof(edges_expected)), 0);
}

TEST_F(Question5Test, Get_correct_nodes_number_to_cover) {
    int num;
    num = read_data("8 1 2 5 6 2 7 1 6 4 5");

    EXPECT_EQ(get_covered_linked_nodes_number(num), 2);
}

TEST_F(Question5Test, break_the_graph_success) {
    int num;
    int node_num;

    num = read_data("4 1 2 2 3 4 3");
    node_num = get_covered_linked_nodes_number(num);

    EXPECT_EQ(node_num, 2);
}

TEST_F(Question5Test, Get_links_already_covered_success) {
    int num;
    int lstate[] = {0, 1, 1, 1, 1, 1, 1};

    num = read_data("6 1 2 2 3 1 4 4 5 5 6");
    //print_cell(num);

    EXPECT_EQ(get_optimal_nodes_number(num), 2);
    EXPECT_EQ(revmove_links_already_covered(num), 1);
    EXPECT_EQ(memcmp(state, lstate, sizeof(lstate)), 0);
    //print_cell(num);
}

TEST_F(Question5Test, brute_force_get_covered_linked_nodes_success) {
    int num;
    int node_num;

    num = read_data("4 1 2 2 3 4 3 1 4");
    node_num = get_covered_linked_nodes_number_by_brute_force(num);

    EXPECT_EQ(node_num, 2);
}

TEST_F(Question5Test, brute_force1) {
    int num;
    num = read_data("8 1 2 5 6 2 7 1 6 4 5");

    EXPECT_EQ(get_covered_linked_nodes_number_by_brute_force(num), 2);
}

TEST_F(Question5Test, brute_force2) {
    int num;
    num = read_data("10 2 3 3 4 4 5 5 2 8 9 9 10 10 8");

    EXPECT_EQ(get_covered_linked_nodes_number_by_brute_force(num), 3);
}

TEST_F(Question5Test, brute_force3) {
    int num;
    num = read_data("12 2 3 3 4 4 5 5 2 8 9 9 10 10 8 5 12 4 11");

    EXPECT_EQ(get_covered_linked_nodes_number_by_brute_force(num), 3);
}

TEST_F(Question5Test, brute_force4) {
    int num;
    num = read_data("13 2 3 3 4 4 5 5 2 8 9 9 10 10 8 5 12 4 11");

    EXPECT_EQ(get_covered_linked_nodes_number_by_brute_force(num), 3);
}
