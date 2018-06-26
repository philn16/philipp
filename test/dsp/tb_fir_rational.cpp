#include <gtest/gtest.h>

#include "dsp/fir_rational.hpp"
#include "tests/test_functions.hpp"
#include "general/defines_includes.hpp"

#define ZEROS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

TEST(fir_rational, test_1_to_1_upr) {
	fir_rational<int, int, int> fir;
	int coeficiants[] = { 1, 2, 3, 9 };
	int inputs[] = { 1, ZEROS };
	int expected[] = { 1, 2, 3, 9, 0, 0, 0 };
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs, LEN(inputs));
	auto output = fir.get_outputs(fir.outputs_avaliable());
	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}

//! tests the initialization function. tests private stuff, and shouldn't be looked at
//! The key to the values is that they should cause the next input to require being taken, and go to the very end
TEST(fir_rational, _init) {
	int coeficiants[] = { 1, 2, 3, 4 };

	fir_rational<int, int, int> fir;
	fir.set_coeficiantes(coeficiants);

	fir.set_resampling_ratios(1, 1);
	ASSERT_EQ(fir.inputs.size(), 4);
	ASSERT_EQ(fir.input_start, -1);

	fir.set_resampling_ratios(3, 2);
	ASSERT_EQ(fir.inputs.size(), 2);
	ASSERT_EQ(fir.input_start, -3);

	fir.set_resampling_ratios(2, 3);
	ASSERT_EQ(fir.inputs.size(), 2);
	ASSERT_EQ(fir.input_start, -1);
}

TEST(fir_rational, test_3_to_1_upr) {
	fir_rational<int, int, int> fir;
	int coeficiants[] = { 1, 2, 3, 4 };
	int inputs[] = { 1, 0 };
	int expected[] = { 1, 2, 3, 4, 0, 0 };
	fir.set_resampling_ratios(3, 1);
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs, LEN(inputs));
	auto output = fir.get_outputs(fir.outputs_avaliable());
	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}

TEST(fir_rational, test_3_to_2_upr) {
	fir_rational<int, int, int> fir;
	int coeficiants[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int inputs[] = { 1, 1, ZEROS };
	// -, ,-, ,-, ,-, ,-, ,-, ,
	// 1,2,3,4,5,6,7,8,9,
	//  ,0,0,1,2,3,4,5,6,7,8,9,
	int expected[] = { 1, 3, 7, 11, 15, 8, 0, 0, 0 };
	fir.set_resampling_ratios(3, 2);
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs, LEN(inputs));
	auto output = fir.get_outputs(fir.outputs_avaliable());
	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}

TEST(fir_rational, test_2_to_3_upr) {
	fir_rational<int, int, int> fir;
	int coeficiants[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int inputs[] = { 1, 1, ZEROS };
	// -, , ,-, , ,-, , ,-, , ,-, , ,
	// 1,2,3,4,5,6,7,8,9,
	//  ,0,1,2,3,4,5,6,7,8,9,
	int expected[] = { 1, 6, 12, 8, 0, 0, 0 };
	fir.set_resampling_ratios(2, 3);
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs, LEN(inputs));
	auto output = fir.get_outputs(fir.outputs_avaliable());
	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}

//! This designed to cause stuff to break
TEST(fir_rational, oddballs) {
	fir_rational<int, int, int> fir;
	// a fir with no coeficiants
	int coeficiants[] = { };
	int inputs[] = { 1, 1, ZEROS };
	int expected[] = { ZEROS };
	fir.set_coeficiantes(coeficiants);
	fir.give_inputs(inputs, LEN(inputs));
	auto output = fir.get_outputs(fir.outputs_avaliable());
	ASSERT_TRUE(assert_lists_equal(expected,output,LEN(expected)));
}

//! Ensures continuation from one round to the next
TEST(fir_rational,multirun) {
	fir_rational<int, int, int> fir;
	int coeficiants[] = { 1, 2, 3, 4 };
	fir.set_coeficiantes(coeficiants);

	for (int i = 0; i < 40; i++) {
		int inputs_1[] = { 1, 0 };
		fir.give_inputs(inputs_1);
		auto &out_1 = fir.get_outputs();
		int expected_1[] = { 1, 2 };
		ASSERT_TRUE(assert_lists_equal(out_1 ,expected_1,LEN(expected_1) ));
		ASSERT_EQ(out_1.size(), LEN(expected_1));

		int inputs_2[] = { 0, 0 };
		fir.give_inputs(inputs_2);
		auto &out_2 = fir.get_outputs();
		int expected_2[] = { 3, 4 };
		ASSERT_TRUE(assert_lists_equal(out_2 ,expected_2,LEN(expected_2) ));
		ASSERT_EQ(out_2.size(), LEN(expected_2));
	}
}

//! Make sure input and output sizes line up
TEST(fir_rational,size_test) {
	int interpolation[] = { 2, 3, 4, 5, 6, 7 };
	int decimation[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
	int coef_sizes[] = { 1, 10, 20, 29 };
	for (auto interp : interpolation)
		for (auto decim : decimation)
			for (auto coef_size : coef_sizes) {
				fir_rational<int, int, int> fir;
				std::vector<int> coefs(coef_size);
				fir.set_coeficiantes(coefs);
				fir.set_resampling_ratios(interp, decim);
				for (int i = 0; i < 5; i++) {
					int input[i * decim];
					fir.give_inputs(input, LEN(input));
					auto& output = fir.get_outputs();
					ASSERT_EQ(output.size(), i * interp);
				}
			}

}
