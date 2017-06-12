#include <limits.h>
#include "gtest/gtest.h"
#include "question1.h"

class Question1Test: public testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(Question1Test, NoFriendsNeedToBeInvited) {
    int extra;
    int follow_level[5] = {1, 1, 1, 1, 1};
    extra = get_extra_friends_number(4, follow_level);

    EXPECT_EQ(extra, 0);
}

TEST_F(Question1Test, OneFriendNeedsToBeInvited) {
    int extra;
    int follow_level[2] = {0, 9};
    extra = get_extra_friends_number(1, follow_level);
    //printf("extra: %d\n", extra);

    EXPECT_EQ(extra, 1);
}

TEST_F(Question1Test, TwoFriendNeedsToBeInvited) {
    int extra;
    int follow_level[6] = {1, 1, 0, 0, 1, 1};
    extra = get_extra_friends_number(5, follow_level);

    EXPECT_EQ(extra, 2);
}

TEST_F(Question1Test, NoFriendsNeedWhenFmaxIs0) {
    int extra;
    int follow_level[1] = {1};
    extra = get_extra_friends_number(0, follow_level);

    EXPECT_EQ(extra, 0);
}

TEST_F(Question1Test, 5FriendsNeedWhenFmaxIs0) {
    int extra;
    int follow_level[6] = {0, 0, 0, 0, 0, 1};
    extra = get_extra_friends_number(5, follow_level);

    EXPECT_EQ(extra, 5);
}

TEST_F(Question1Test, 5FriendsNeeded) {
    int extra;
    int follow_level[6] = {0, 0, 0, 0, 0, 1};
    extra = get_extra_friends_number(5, follow_level);

    EXPECT_EQ(extra, 5);
}

TEST_F(Question1Test, 4FriendsNeeded) {
    int extra;
    int follow_level[6] = {1, 0, 0, 0, 0, 1};
    extra = get_extra_friends_number(5, follow_level);

    EXPECT_EQ(extra, 4);
}

TEST_F(Question1Test, TestFriendsNeeded) {
    int extra;
    int follow_level[6] = {1, 1, 0, 4, 0, 1};
    extra = get_extra_friends_number(5, follow_level);

    EXPECT_EQ(extra, 1);
}
