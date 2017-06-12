#include <limits.h>
#include "gtest/gtest.h"
#include "question3.h"

class Question4Test: public testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(Question4Test, StateIsOffIfNoSnap) {
    int state;

    state = snap_fingers(1, 0);
    EXPECT_EQ(state, OFF);
}

TEST_F(Question4Test, StateIsOnWhenOneSnap) {
    int state;

    state = snap_fingers(1, 1);
    EXPECT_EQ(state, ON);
}

TEST_F(Question4Test, StateIsOFFIfNoSnap1) {
    int state;

    state = snap_fingers(4, 0);
    EXPECT_EQ(state, OFF);
}

TEST_F(Question4Test, StateIsOnAfter47Snaps) {
    int state;

    state = snap_fingers(4, 47);
    EXPECT_EQ(state, ON);
}
