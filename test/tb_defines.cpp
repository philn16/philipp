
#include "defines.hpp"
#include <gtest/gtest.h>


TEST(defines, test1){
int test_1[]={1,2,3,4,5};
ASSERT_EQ(LEN(test_1),5);

#if 0
FAILURE_MESSAGE("This is a failure message");
SUCESS_MESSAGE("This is a sucess message");
WARNING_MESSAGE("This is a warning message");
#endif
}
