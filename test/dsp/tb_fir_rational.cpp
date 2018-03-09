#include <gtest/gtest.h>

#include "dsp/fir_rational.hpp"
#include "tests/test_functions.hpp"
#include "general/defines_includes.hpp"

#define ZEROS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

TEST(fir_rational, test_1_to_1_upr) {
	fir_rational<int,int,int> fir;
	int coeficiants[]= {1,2,3,4};
	int inputs[]= {1,ZEROS};
	int expected[]= {1,2,3,4,0,0,0};
	int *output;

	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs,LEN(inputs));
	output = &fir.get_outputs(fir.outputs_avaliable())[0];

	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}


TEST(fir_rational, test_3_to_2_upr) {
	fir_rational<int,int,int> fir;
	int coeficiants[]= {1,2,3,4,5,6,7,8,9};
	int inputs[]= {1,1,ZEROS};
	// -, ,-, ,-, ,-, ,-, ,-, ,
	// 1,2,3,4,5,6,7,8,9,
	//  ,0,0,1,2,3,4,5,6,7,8,9,
	int expected[]= {1,3,7,11,15,8,0,0,0};
	int *output;

	fir.set_resampling_ratios(3,2);
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs,LEN(inputs));
	output = &fir.get_outputs(fir.outputs_avaliable())[0];

	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}


TEST(fir_rational, test_2_to_3_upr) {
	fir_rational<int,int,int> fir;
	int coeficiants[]= {1,2,3,4,5,6,7,8,9};
	int inputs[]= {1,1,ZEROS};
	// -, , ,-, , ,-, , ,-, , ,-, , ,
	// 1,2,3,4,5,6,7,8,9,
	//  ,0,1,2,3,4,5,6,7,8,9,
	int expected[]= {1,6,12,8,0,0,0};
	int *output;

	fir.set_resampling_ratios(3,2);
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs,LEN(inputs));
	output = &fir.get_outputs(fir.outputs_avaliable())[0];

	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}
