#include <vector>
#include <sys/types.h>
/**
The vector queue is a queue that on average is O(1) for pushing new elements to the back while allowing for sequential acess of data. 
The basic algorithm is that it uses more data then it needs. When the end of the memory space is reached, it moves everything to the start
Possible uses:
--------------
Storing the states of a fir filter as a queue operaation is desired, but you want to be able to acess elements sequentially

*/
template <typename dataType>
class vector_queue{
	private:
	std::vector<dataType> data;
	
	public:
	//! Pop the front by ammountToPop elements
	bool pop_front(int ammountToPop){
		
	}
	size_t getSize(){
		return data.size();
	}
	
	dataType operator[](int loc){
		return data[loc];
	}
	
	
	
	
};
