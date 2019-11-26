 
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<fstream>
#include<pthread.h>
#include<algorithm>
#include<fstream>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<list>
#include<climits>
#include <errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<fcntl.h>

#define expand_threshold 0.00001
#define default_threads 10

using namespace std;

struct threadpool
{
	int threads;
	queue<pthread_t> free_threads;
};

struct pack
{
	threadpool *tp;
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

void expand_pool(threadpool& tp, int new_size)
{
	cout<<"expandig threadpool from "<<tp.threads<<" to "<<new_size<<endl;
	for(int lv=1; lv <= new_size - tp.threads; lv++)
	{
		pthread_t nt;
		tp.free_threads.push(nt);
	}
	tp.threads = new_size;
}


pthread_t dispatch(threadpool& from_me)
{
    cout<<"\nfree threads queue size Dispatch "<<from_me.free_threads.size()<<endl;
    clock_t start = clock();
    clock_t curr;
    // cout<<"Free thread size : "<<from_me.free_threads.size()<<endl;
    while(from_me.free_threads.size() == 0)
    {
        curr = clock();
        if(curr > expand_threshold)
        {
            cout<<"calling expand pool\n";
            expand_pool(from_me, from_me.threads*2);
            break;
        }
    }
    pthread_t ft = from_me.free_threads.front();
    // cout<<"popped out thread id "<<ft<<endl;
    // cout<<" thread id at front "<<from_me.free_threads.front()<<endl;
    from_me.free_threads.pop();

    return ft;
}




void destroy_threadpool(threadpool *destroyme)
{
	delete destroyme;
}