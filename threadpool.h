#include<iostream>
#include<vector>
#define default_threads 50
using namespace std;

struct threadpool
{
	int threads;
	vector<pthread_t> thread_vector;
	vector<bool> busy_threads;
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
		new_pool.free_threads.push_back(false);
	}
	cout<<"address of returned pool "<<&new_pool<<endl;
	return new_pool;
}

void dispatch(threadpool from_me, void* func_ptr, void *arg)
{
	for(int lv = 0; lv < from_me.threads; lv++)
	{
		if(from_me.busy_threads[lv] == false)
			pthread_create(thread_vector[lv], NULL, *func_ptr, arg);
	}
}

void expand_pool(threadpool& tp, int new_size)
{
	tp.thread_vector.resize(new_size);
	tp.threads = new_size;
	tp.busy_threads.resize(new_size);
}


void destroy_threadpool(threadpool destroyme)
{

}
