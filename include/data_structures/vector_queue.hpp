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
	//! This is where vector queue gets it's name; this contains the data
	std::vector<dataType> data;
	//! This affects how much extra memory is used. It's a multiplyer. If this were one and things somehow still woked it'd be really slow as pushing a new element would require moving the queue each time
	int mult=4;
	//! Tracks the start of valid indexes (note end takes priority)
	int begin=0;
	//! Tracks the first invalid index location
	int end=0;
	//! Move the data back to the front of avaliable memory
	void shitToFront(){
		auto newEnd=size();
		// shift the data to the "left"
		for(int write=0,read=begin; read != end; read++,write++)
		data[write]=data[read];
		// update the start and end indexes to reflect the move
		begin=0;
		end=newEnd;
	}
	
	public:
	vector_queue(){
		data.resize(mult);
	}
	//! Set how much extra data is to be stored (for performancce). Note this should be larger than 1
	void set_mult(int mult){
		this->mult=mult;
	}
	//! Pop the front by ammountToPop elements. Starts poping values at index 0. Undefined behavior happens if you pop more than what's returned by size()
	void pop_front(int ammountToPop){
		begin += ammountToPop;
	}
	//! pop the back (starting at index size()-1) by ammountToPop elements. Undefined behavior happens if you pop more than what's returned by size()
	void pop_back(int ammountToPop){
		end -= ammountToPop;
	}
	//! pushes values to the back. For example, if we already had [0,1,2,3] and fed this [4,5,6] we'd end up with [0,1,2,3,4,5,6]
	template<typename arrayT>
	void push_back(arrayT input, int ammount){
		// move everything to the front if we've reached the end
		if ( end+ammount >= data.size())
			shitToFront();
			// ammount of elements in use after finnishing the push
		auto afterAddAmmount=ammount+end;
		// allocate more data if nessesary
		if( afterAddAmmount > data.size() )
		data.resize(afterAddAmmount*mult);
		// add the lements to the back
		for(int i=0; end != afterAddAmmount; end++,i++)
		data[end]=input[i];
	}
	//! returns the size of data valid data (ignoring extra allocated stuff)
	size_t size(){
		return end-begin;
	}
	//! Acess valid data
	dataType& operator[](int loc){
		return data[begin+loc];
	}
	
	
	
	
};
