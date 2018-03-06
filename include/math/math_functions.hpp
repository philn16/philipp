// some generic functions
#pragma once


// Returns the dot product of 2 arrays. The dot product is the sum of the element wise multiplication
template <typename array1, typename array2, typename outputT>
outputT dotProduct(array1 a, array2 b, int len) {
	outputT sum=0;
	for(int i=0; i<len; i++)
		sum+=a[i]*b[i];
	return sum;
}
