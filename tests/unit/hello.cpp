#include <gtest/gtest.h>

TEST(ExampleTest, AlwaysPasses)
{
    EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
