#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>
// #include<dos.h>
// #include"threadpool.h"
#define MAX 80 
#define PORT 6584 
#define SA struct sockaddr 
#define max_requests 500
using namespace std;

int sockfd, connfd; 
struct sockaddr_in servaddr, cli; 

void func(int sockfd, int counter) 
{ 
	char buff[MAX]; 
	int n; 
	int i=1;
	while(i--){ 
		bzero(buff, sizeof(buff)); 
		// printf("Enter the string : "); 
		n = 0; 
		// while ((buff[n++] = getchar()) != '\n') 
		// 	; 
				cout<<"sending to server"<<counter<<endl;

		write(sockfd, &counter, sizeof(counter)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("From Server : %s %d", buff, counter); 

		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

void *connect_func(void *arg)
{
	int counter = *(int*) arg;
	cout<<"req number "<<counter<<"\n";
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{ 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	// else
	// 	printf("connected to the server..\n"); 


	func(sockfd, counter);
}

int main() 
{ 
	

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 

	pthread_t client_thread[1000];
	int counter = 1;
	while(counter <= max_requests)
	{
		//sleep(1);
        usleep(int(1e5));
		int local = counter;
		// cout<<"sending to connect"<<local<<endl;
		// sleep(1);
		pthread_create(&client_thread[counter], NULL, connect_func, &local);

		
		++counter; 

	}

	

	// function for chat 
	

	// close the socket 
	close(sockfd); 
} 
