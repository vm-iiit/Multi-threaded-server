#include<iostream>
#include<vector>
#include<queue>
#include<pthread.h>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include<time.h>

#define expand_threshold 5.00
#define default_threads 50
#define PORT 8080
using namespace std;

struct threadpool
{
	int threads;
	queue<pthread_t> free_threads;
};

struct pack
{
	threadpool tp;
	pthread_t thread_id;
};


threadpool *create_threadpool(int num_threads = default_threads)
{
	threadpool *new_pool = new threadpool();
	new_pool->threads = num_threads;
	
	while(new_pool->free_threads.size())
		new_pool->free_threads.pop();

	for(int lv = 1; lv <= num_threads; lv++)
	{
		pthread_t new_thread;
		new_pool->free_threads.push(new_thread);
	}
	// cout<<"address of returned pool "<<&new_pool<<endl;
	return new_pool;
}




pthread_t dispatch(threadpool from_me)
{
	clock_t start = clock();
	clock_t curr;
	while(from_me.free_threads.size() == 0)
	{
		curr = clock();
		if(curr > expand_threshold)
		{
			expand_pool(from_me, from_me.threads*2);
			break;
		}
	}
	pthread_t ft = from_me.free_threads.front();
	from_me.free_threads.pop();

	return ft;
}


void expand_pool(threadpool tp, int new_size)
{
	for(int lv=1; lv <= new_size - tp.threads; lv++)
	{
		pthread_t nt;
		tp.free_threads.push(nt);
	}
	tp.threads = new_size;
}


void destroy_threadpool(threadpool *destroyme)
{
	delete destroyme;
}