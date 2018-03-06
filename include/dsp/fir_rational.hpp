#pragma once
#include <vector>
#include "../data_structures/vector_queue.hpp"
#include "../math/math_functions.hpp"
/**
This is a rational FIR (finite impulse response) filter class. A rational FIR is an extension of the normal FIR filter; that is, a normal FIR has a fixed interpolation and decimation ratio of 1 to 1. As a result, a rational FIR fully covers the properties of a normal FIR

Possible uses:
--------------
* Resampling
* Filtering

*/
template <typename inputT, typename coeficiantT=inputT, typename outputT=inputT>
class fir_rational {
  private:
	int interpolationRatio=1, decimationRatio=1;
	int numTaps=0;
	//! The input also includes the states since states are just previous inputs
	vector_queue<inputT> inputs;
	vector_queue<outputT> outputs;
	//! The things that are multiplied by the states to get the output
	std::vector< coeficiantT > coeficiants;

  public:
	//! Example: if interpolationRatio is 3 and decimationRatio is 2 then there will be 3 outputs for every input. \note This is an initialization function.
	void set_resampling_ratios(int interpolationRatio=1, int decimationRatio=1) {
		this->interpolationRatio=interpolationRatio;
		this->decimationRatio=decimationRatio;
	}

	//! Set the FIR coeficiants (also called taps). The states are multiplied by the coeficiants and the sumed to give the output. \note This is an initialization function.
	template< typename coeficiantArray>
	void set_coeficiantes(int numTaps, coeficiantArray coefs) {
		coeficiants.resize(numTaps);
		for(int i=0; i<numTaps; i++)
			coeficiants[i]=coefs[i];
		// setup the initial inputs / states with 0s
		inputT zero[]= {inputT(0)};
		for(int i=0; i<numTaps-1; i++)
			inputs.push_back(zero,1);
	}

	//! takes in inputs and calculates the outputs
	template<typename inputStruct>
	void give_inputs(inputStruct in, int ammount) {
		inputs.push_back(in,ammount);

	}

	//! returnes an array of output values and (depending on the mode) the number of output values
	//! It's expected that the user might pass outputs_avaliable() in "int toTake" if they wanted to take all outputs
	//! if adjust_output_size is true then the output will automatically point to the next unseen data (so the user doens't need to manually do that)
	outputT* get_outputs(int toTake, bool adjust_output_size=true) {
		return &outputs[0];
	}

	//! Returns the number of valid outputs
	int outputs_avaliable() {
		return 0;
	}

};
