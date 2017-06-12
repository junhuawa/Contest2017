#include <limits.h>
#include "gtest/gtest.h"
#include "question2.h"

class Question2Test: public testing::Test {
    protected:
        virtual void SetUp() {
            init_task();
        }

        virtual void TearDown() {
        }
};

TEST_F(Question2Test, InsertTaskSuccessful) {
    long subtask[10] = {4, 5};

    insert_task(1, 3, subtask);
    //printf("%ld, %ld\n", tasklist[1].subtask[0], tasklist[1].subtask[1]);
    
    EXPECT_EQ(tasklist[1].subtask[0], subtask[0]);
    EXPECT_EQ(tasklist[1].subtask[1], subtask[1]);
    EXPECT_EQ(nodeid[0], 1);
    EXPECT_EQ(tree[0], -1);
    EXPECT_EQ(nodeid[1], 3);
    EXPECT_EQ(tree[1], 0);
}

TEST_F(Question2Test, InsertExampleTaskSuccessful) {
    long subtask[3][10] = {{1, 2, 3}, {4, 5}, {8}};
    int count;

    insert_task(1, 2, subtask[0]);
    insert_task(1, 3, subtask[1]);
    count = insert_task(3, 9, subtask[2]);

    EXPECT_EQ(count, 4);

    EXPECT_EQ(tasklist[1].subtask[0], subtask[0][0]);
    EXPECT_EQ(tasklist[1].subtask[1], subtask[0][1]);
    EXPECT_EQ(tasklist[1].subtask[2], subtask[0][2]);

    EXPECT_EQ(tasklist[2].subtask[0], subtask[1][0]);
    EXPECT_EQ(tasklist[2].subtask[1], subtask[1][1]);

    EXPECT_EQ(tasklist[3].subtask[0], subtask[2][0]);

    EXPECT_EQ(nodeid[0], 1);

    EXPECT_EQ(tree[0], -1);
    EXPECT_EQ(tree[1], 0);
    EXPECT_EQ(tree[2], 0);
    EXPECT_EQ(tree[3], 2);

    EXPECT_EQ(nodeid[0], 1);
    EXPECT_EQ(nodeid[1], 2);
    EXPECT_EQ(nodeid[2], 3);
    EXPECT_EQ(nodeid[3], 9);

}

TEST_F(Question2Test, TellTaskResultBeforeTaskInsert) {
    long subtask[3][10] = {{1, 2, 3}, {4, 5}, {8}};
    int count;

    insert_task(1, 2, subtask[0]);
    tell_result(3, 4, SUCCESS);
    count = insert_task(1, 3, subtask[1]);

    EXPECT_EQ(tasklist[2].results[0], SUCCESS);
}

TEST_F(Question2Test, TellTaskResultBeforeTaskInsert1) {
    long subtask[3][10] = {{1, 2, 3}, {4, 5}, {8}};

    insert_task(1, 2, subtask[0]);
    tell_result(3, 5, SUCCESS);
    tell_result(3, 4, FAIL);
    insert_task(1, 3, subtask[1]);

    EXPECT_EQ(tasklist[2].results[1], SUCCESS);
    EXPECT_EQ(tasklist[2].results[0], FAIL);

    EXPECT_EQ(tasklist[2].subtask[0], 4);
    EXPECT_EQ(tasklist[2].subtask[1], 5);
}

TEST_F(Question2Test, TellTaskResultSuccessful) {
    long subtask[3][10] = {{1, 2, 3}, {4, 5}, {8}};
    int count;

    insert_task(1, 2, subtask[0]);
    tell_result(2, 1, SUCCESS);
    tell_result(2, 2, SUCCESS);
    tell_result(2, 3, FAIL);
    tell_result(3, 4, SUCCESS);
    count = insert_task(1, 3, subtask[1]);
    tell_result(3, 5, SUCCESS);
    count = insert_task(3, 9, subtask[2]);
    tell_result(9, 8, FAIL);
    print_report();
    

    //printf("count: %d\n", count);
    EXPECT_EQ(count, 4);
    EXPECT_EQ(tasklist[1].results[0], SUCCESS);
    EXPECT_EQ(tasklist[1].results[1], SUCCESS);
    EXPECT_EQ(tasklist[1].results[2], FAIL);
    

    //printf("tasklist[2]: %ld, res: %d, subtask: %ld, res: %d\n", 
    //        tasklist[2].subtask[0], tasklist[2].results[0], tasklist[2].subtask[1], tasklist[2].results[1]);
    EXPECT_EQ(tasklist[2].results[0], SUCCESS);
    EXPECT_EQ(tasklist[2].results[1], SUCCESS);
}

TEST_F(Question2Test, TestParseInsertCmd) {
    long subtask[] = {7737322923756243546, 1729325627670020948, 2519085799012976362, 234556};
    parse_insert_cmd("{-5846402106818935796, 89503850849454692, List(7737322923756243546, 1729325627670020948, 2519085799012976362, 234556)}");

    EXPECT_EQ(nodeid[0], -5846402106818935796);
    EXPECT_EQ(nodeid[1], 89503850849454692);
    EXPECT_EQ(tree[1], 0);

    for(int i=0; i<4; i++){
        EXPECT_EQ(tasklist[1].subtask[i], subtask[i]);
    }
}

TEST_F(Question2Test, TestResultTell) {
    long subtask[] = {1, 2, 3};
    int results[] = {SUCCESS, SUCCESS, FAIL};

    parse_insert_cmd("{1, 2, List(1, 2, 3)}");
    parse_tell_result("{2, 1, Success}");
    parse_tell_result("{2, 2, Success}");
    parse_tell_result("{2, 3, FAIL}");
    parse_tell_result("{3, 4, Success}");

    EXPECT_EQ(nodeid[0], 1);
    EXPECT_EQ(nodeid[1], 2);
    EXPECT_EQ(tree[1], 0);

    for(int i=0; i<3; i++){
        EXPECT_EQ(tasklist[1].subtask[i], subtask[i]);
        EXPECT_EQ(tasklist[1].results[i], results[i]);
    }

    EXPECT_EQ(tasklist[2].results[0], SUCCESS); 
    EXPECT_EQ(tasklist[2].subtask[0], 4); 
}

TEST_F(Question2Test, 2PackFromOneSrcNodeFailed) {
    long subtask[] = {1, 2, 3};
    int results[] = {SUCCESS, SUCCESS, FAIL};

    parse_insert_cmd("{1, 2, List(1, 2, 3)}");
    parse_tell_result("{2, 1, Success}");
    parse_tell_result("{2, 2, Success}");
    parse_tell_result("{2, 3, FAIL}");
    parse_tell_result("{3, 4, Success}");
    parse_insert_cmd("{1, 3, List(4, 5)}");
    parse_tell_result("{3, 5, Fail}");

    print_report();
}

TEST_F(Question2Test, 2PackFromOneSrcNodeFailed1) {
    long subtask[] = {1, 2, 3};
    int results[] = {SUCCESS, SUCCESS, FAIL};

    /*
    for(int i=0; i<3; i++){
        printf("%d\n", tasklist[1].results[i]);
    }
    */
    parse_insert_cmd("{1, 2, List(1, 2, 3)}");
    parse_insert_cmd("{1, 3, List(4, 5)}");
    parse_insert_cmd("{3, 9, List(6, 7)}");
    

    /*
   // printf("Result: \n");
    for(int i=0; i<3; i++){
        printf("%d\n", tasklist[1].results[i]);
    }
    */
    print_report();
}
