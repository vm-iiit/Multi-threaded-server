#include<iostream>
#include<vector>
#define default_threads 50
using namespace std;

struct threadpool
{
	int threads;
	vector<pthread_t> thread_vector;
};

threadpool create_threadpool(int num_threads = default_threads)
{
	threadpool new_pool;
	new_pool.threads = num_threads;
	new_pool.thread_vector.clear();

	for(int lv = 1; lv <= num_threads; lv++)
	{
		pthread_t new_thread;
		new_pool.thread_vector.push_back(new_thread);
	}
	cout<<"address of returned pool "<<&new_pool<<endl;
	return new_pool;
}

// void dispatch(threadpool from_me, dispatch_fn dispatch_to_here, void *arg)
// {

// }


// void destroy_threadpool(threadpool destroyme)
// {

// }
