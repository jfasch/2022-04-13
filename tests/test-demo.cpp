#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;


TEST(MyFirstSuite, Ok)
{
    // just passes
}

TEST(MyFirstSuite, Fail)
{
    FAIL();
}

TEST(MyFirstSuite, AssertEqual)
{
    int some_variable = 42;
    ASSERT_EQ(some_variable, 666) << "argh, this went seriously wrong";
}

class SimpleFixture : public ::testing::Test
{
protected:
    void SetUp()
    {
        cerr << "creating something" << endl;
        something = new char[]{"something"};
    }
    void TearDown()
    {
        cerr << "removing something" << endl;
        delete[] something;
    }

    char* something;
};

TEST_F(SimpleFixture, MyFirstSuite)
{
    string my_str = "something";
    ASSERT_EQ(my_str, something);
}
