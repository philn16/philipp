#include <gtest/gtest.h>

#include "someFile.hpp"


TEST(somename, somefunction) {
	ASSERT_EQ(1,1);
}

int main(int argc, char* argv[]) {
	//sayHi();

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
