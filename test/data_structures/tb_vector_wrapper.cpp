#include <gtest/gtest.h>
#include "data_structures/vector_wrapper.hpp"
#include "general/defines_includes.hpp"

TEST(vector_wrapper, test1) {
	vector_wrapper<long> macklemore;
	long array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	macklemore.set_wrapper(&array[0], &array[LEN(array)]);

	for (long &index : macklemore)
		index *= 3;

	ASSERT_EQ(macklemore.size() , LEN(array));

	for (int i = 0; i < LEN(array); i++)
		ASSERT_EQ(i * 3, macklemore[i]);

}
