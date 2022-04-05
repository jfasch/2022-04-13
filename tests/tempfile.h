#ifndef TESTS_TEMPFILE_H
#define TESTS_TEMPFILE_H

#include <gtest/gtest.h>

#include <unistd.h>
#include <stdlib.h>
#include <string>


class TempfileFixture : public ::testing::Test
{
protected:
    void SetUp()
    {
        char tmpfile[] = "clean-code-XXXXXX";
        tempfd = mkstemp(tmpfile);
        ASSERT_GE(tempfd, 0);
        tempname = tmpfile;
    }

    void TearDown()
    {
        ::close(tempfd);
        ::unlink(tempname.c_str());
    }

    std::string tempname;
    int tempfd;
};

#endif
