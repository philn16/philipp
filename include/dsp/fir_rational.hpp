#pragma once
#include <vector>
#include "../data_structures/vector_queue.hpp"
#include "../math/math_functions.hpp"
#include "../general/defines_includes.hpp"
/**
This is a rational FIR (finite impulse response) filter class. A rational FIR is an extension of the normal FIR filter; that is, a normal FIR has a fixed interpolation and decimation ratio of 1 to 1. As a result, a rational FIR fully covers the properties of a normal FIR

Possible uses:
--------------
* Resampling
* Filtering

*/
template <typename inputT, typename coeficiantT=inputT, typename outputT=inputT>
class fir_rational {
//   private:
  public:
	int interpolationRatio=1, decimationRatio=1;
	int numTaps=0;
	//! The input also includes the states since states are just previous inputs
	vector_queue<inputT> inputs;
	vector_queue<outputT> outputs;
	//! The things that are multiplied by the states to get the output
	std::vector< coeficiantT > coeficiants;
	//! keeps track of the last ammount of coeficiants the user requested
	int outputsToTake=0;
	//! keeps track of when an input should be taken
	int noDecimationOut = 1;
	//! position where input values start being multiplied by the taps
	int input_start = 0;


  public:
	//! shared initialization.
	//! allow first output to be the first input multiplied by the first state
	void _init() {
		inputs.empty();
		// setup the initial inputs / states with 0s
		inputT zero[]= {inputT(0)};
		// total size of inital input values including the soon to be new one
		int total = (coeficiants.size()+interpolationRatio-1)/interpolationRatio;
		// see if there's room for extra 0 inputs before the main corse
		for(int i=0; i< total ; i++)
			inputs.push_back(zero,1);
		// now for determining the start location
		input_start = coeficiants.size() - (total)*interpolationRatio-1;
	}

	//! Example: if interpolationRatio is 3 and decimationRatio is 2 then there will be 3 outputs for every input. \note This is an initialization function.
	//! interpolation causes the input to be filled with zeros, while decimation causes outputs to be skiped. As a result, interpolation zooms out of the spectrum and decimation zooms in.
	void set_resampling_ratios(int interpolationRatio=1, int decimationRatio=1) {
		this->interpolationRatio=interpolationRatio;
		this->decimationRatio=decimationRatio;
		_init();
	}

	//! Set the FIR coeficiants (also called taps). The states are multiplied by the coeficiants and the sumed to give the output. \note This is an initialization function.
	//! The UPR for a 1 to 1 filter is coefs[0]+z^{-1}coefs[1]+z^{-2}coefs[2]+...
	template< typename coeficiantArray>
	void set_coeficiantes(coeficiantArray& coefs) {
		// the newest values (which appear at the back) are multiplied by the first coeficiants, so it makes sense for the first coeficiants to be at the back
		std::vector< coeficiantT > coef_vec;
		for( auto coef : coefs )
			coef_vec.push_back(coef);
		// reset the current coeficiants each time
		coeficiants.resize(0);
		// reverse the order of the coeficiants for easier multiplying later
		for(int i=coef_vec.size()-1; i >= 0 ; i--)
			coeficiants.push_back(coef_vec[i]);
		_init();
	}

	//! takes in inputs and calculates the outputs
	template<typename inputStruct>
	void give_inputs(inputStruct in, int ammount) {
		inputs.push_back(in,ammount);
// keep going as long as there are enough inputs
		while( true) {
			//cout << "cursize:  " << inputs.size() << endl;
			//cout << "in start: " << input_start << endl;

			// set up the next input
			while(input_start < 0) {
				// there's not enough input for a cycle - come back next time
				if ( input_start + inputs.size() * interpolationRatio <= coeficiants.size())
					return;
				// make way for the newer data
				inputs.pop_front(1);
				// don't process 0s
				input_start += interpolationRatio;
			}
			//cout << "cursize:  " << inputs.size() << endl;
			//cout << "in start: " << input_start << endl;
			outputT sum=0;
			// multiply the inupts by the coeficiants accounting for 0s due to interpolation
			int input_count=0;
			for( int position = input_start; position < coeficiants.size(); position += interpolationRatio) {
				//cout << position << " " << input_count << " " <<inputs[input_count] << endl;
				sum += coeficiants[position] * inputs[input_count];
				input_count++;
			}
			//cout << endl;
			outputs.push_back(&sum);
			input_start -= decimationRatio;
		}
	}

	//! returnes an array of output values and (depending on the mode) the number of output values
	//! It's expected that the user might pass outputs_avaliable() in "int toTake" or the default value -1 if they wanted to take all outputs
	//! if adjust_output_size is true then the output will automatically point to the next unseen data (so the user doens't need to manually do that)
	decltype(outputs)& get_outputs(int toTake=-1, bool adjust_output_size=true) {
		// adjust the take value
		if ( toTake == -1 )
			toTake=outputs.size();
		// make it so the next round through doesn't pop the front
		if ( adjust_output_size == false )
			toTake=0;
		// pop away what was already given
		outputs.pop_front(this->outputsToTake);
		// prepare for the next poping
		this->outputsToTake=toTake;
		// give the output
		return outputs;
	}

	//! Returns the number of valid outputs
	int outputs_avaliable() {
		return outputs.size();
	}

};

