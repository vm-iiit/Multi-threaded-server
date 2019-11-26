all:
	g++ server.cpp threadpool.h req_generator.cpp -o main.out -pthread