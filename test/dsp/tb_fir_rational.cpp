#include <gtest/gtest.h>

#include "dsp/fir_rational.hpp"
#include "tests/test_functions.hpp"
#include "general/defines_includes.hpp"

#define ZEROS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

TEST(fir_rational, test1) {
	fir_rational<int,int,int> fir;
	int coeficiants[]= {1,2,3,4};
	int inputs[]= {1,ZEROS};
	int expected[]= {1,2,3,4,0,0,0};
	int *output;

	fir.give_inputs(inputs,LEN(inputs));
	output = fir.get_outputs(fir.outputs_avaliable());

	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
	//fir.giveInputs(inputs);
	//ASSERT_EQ(1,1);
}
