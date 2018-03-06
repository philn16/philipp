// some usefull functions
#pragma once
//#include "general/defines.hpp"
#include "general/defines_includes.hpp"

template<typename array>
void array_print(array a,int len) {
	cout << "[";
	for(int i=0; i < len-1; i++)
		cout << a[i] << ", ";
	cout << a[len-1] << "]" << endl;
}

//! Compares n values element wise values of 2  datastructures that support the [] operator. Returns true if all elements are equal
template<typename array_1, typename array_2>
bool assert_lists_equal(array_1 a, array_2 b, int len) {
	bool equal=true;
	for(int i=0; i < len; i++)
		equal &= a[i]==b[i];
	if( ! equal ) {
		cout << "Data not equal:"<<endl;
		array_print(a,len);
		array_print(b,len);
	}
	return equal;
}


