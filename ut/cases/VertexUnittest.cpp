#include <limits.h>
#include "gtest/gtest.h"
#include "question2.h"

class Question5Test: public testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(Question5Test, InsertTaskSuccessful) {
    EXPECT_EQ(1, 1);
}

