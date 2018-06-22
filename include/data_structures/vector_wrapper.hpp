#pragma once

/** Takes an annay / datatype as input and provides a size function and iterators
 * Note this has no deconstruction; it "packages" current data
 */
template<class dataT>
class vector_wrapper {
public:
	//! Return the first valid pointer
	dataT* begin() {
		return _begin;
	}
	//! Return the first invalid pointer
	dataT *end() {
		return _end;
	}
	//! Return the number of valid elements
	int size() {
		return _end - _begin ;
	}
	//! Set the wrapper based on an existing array
	void set_wrapper(dataT *begin, dataT *end) {
		this->_begin = begin;
		this->_end = end;
	}
	dataT *_begin = nullptr, *_end = nullptr;

	//! Acess wrapper elements
	dataT operator[](int index){
		return *(begin()+index);
	}
};
