#include "threadpool.h"
#include<queue>
#include<stdio.h>
#include<string.h>
// #include<pthread.h>

queue<int> request;

// struct dispatch_args
// {

//     threadpool obj;
//     // void * func_ptr;
//     void * args;

// };


void *thread_worker(void * soc)
{
	int new_socket = *(int *) soc;

	char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    int valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    return NULL;
}

void *wait(void *tid)
{
	pack new_p = *(pack *)tid;

	if(pthread_join(new_p.thread_id, NULL))
		new_p.tp.free_threads.push(new_p.thread_id);
	return NULL;
}

void* dispatch_helper(void* args)
{
	threadpool obj = *(threadpool*)args;
// void* func_p = &(dispatch_args*)args.func_ptr;
	// void* arg = &(dispatch_args*)args.args;

	while(1)
	{
    	if(request.size())
    	{
        	int socid = request.front();
        	request.pop();
	        pthread_t nt = dispatch(obj);
	        // dispatch(*obj,func_p,arg)
	        pthread_create(&nt, NULL, thread_worker, &socid);
	        
	        pthread_t h_thread;
	        pack p;
	        p.tp = obj;
	        p.thread_id = nt;
	        pthread_create(&h_thread, NULL, wait, &p);
	    }
	}
}

int main()
{

	// cout<<"address of received pool :"<<&test_pool_2<endl;
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    socklen_t addrlen = sizeof(address); 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    threadpool *test_pool= create_threadpool(5);
    

    pthread_t dispatcher;


    // dispatch_args da;

    // da.obj = test_pool; 
    // da.func_ptr(void*) = &thread_worker;
    // // da.args = (void *)new_socket

    pthread_create(&dispatcher,NULL,dispatch_helper, test_pool);

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen))>0) 
    {            
           // dispatch(test_pool,thread_worker,(void *)new_socket);
           request.push(new_socket);
    
    } 
    
	return 0;
}