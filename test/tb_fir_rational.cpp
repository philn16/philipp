#include <gtest/gtest.h>

#include "dsp/fir_rational.hpp"

TEST(fir_rational, test1) {
	fir_rational<int,int,int> fir;

	std::vector<int> inputs(4);
	inputs[0]=0;
	inputs[1]=1;
	inputs[2]=2;
	inputs[3]=3;
	fir.giveInputs(inputs);
	ASSERT_EQ(1,1);
}
