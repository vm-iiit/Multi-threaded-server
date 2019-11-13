#include "threadpool.h"

int main()
{
	threadpool test_pool = create_threadpool();
	cout<<"address of received pool :"<<&test_pool<<endl;

	threadpool test_pool_2 = create_threadpool(5);
	cout<<"address of received pool :"<<&test_pool_2<<endl;
	return 0;
}