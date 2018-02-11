#include "data_structures/vector_queue.hpp"
#include "defines.hpp"
#include <gtest/gtest.h>


TEST(vector_queue, test1){

vector_queue<int> uut;

int in_1[]={0,1,2,3,4,5};
uut.push_back(in_1,LEN(in_1));
for(int i=0; i <= 5; i++)
ASSERT_EQ(uut[i],i);
ASSERT_EQ(uut.size(),6);

int in_2[]={6,7,8,9,10,11};
uut.push_back(in_2,LEN(in_2));
for(int i=0; i <= 11; i++)
ASSERT_EQ(uut[i],i);
ASSERT_EQ(uut.size(),12);

uut.pop_front(5);
ASSERT_EQ(uut.size(),7);
for(int index=0,value=5; index<7; index++, value++)
ASSERT_EQ(uut[index],value);

// clear out everythin
uut.pop_front(uut.size());

// test a large allocation and handeling of std::vector
std::vector<int> in_3(20000);
for(int i=0;i<in_3.size();i++)
in_3[i]=i*i%13+i*i;
uut.push_back(in_3,in_3.size());
for(int i=0; i < in_3.size(); i++)
ASSERT_EQ(uut[i],in_3[i]);

}


