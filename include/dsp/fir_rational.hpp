#pragma once
#include <vector>

/**
This is a rational FIR (finite impulse response) filter class. A rational FIR is an extension of the normal FIR filter; that is, a normal FIR has a fixed interpolation and decimation ratio of 1 to 1. As a result, a rational FIR fully covers the properties of a normal FIR
 
Possible uses:
--------------
* Resampling
* Filtering



*/
template <typename inputT, typename coeficiantT=inputT, typename outputT=inputT>
class fir_rational{
	private:
	int interpolationRatio=1, decimationRatio=1;
	int numTaps=0;
	std::vector<inputT> inputs;
	std::vector<outputT> outputs;
	
	public:
	void set_resampling_ratios(int interpolationRatio=1, int decimationRatio=1){
		this->interpolationRatio=interpolationRatio;
		this->decimationRatio=decimationRatio;
	}
	
	template<typename inputStruct> 
	void giveInputs(inputStruct in){
		inputs.resize(in.size());
		//inputs.pop_front(3);
		
	}
	
	
	
	
	
};
