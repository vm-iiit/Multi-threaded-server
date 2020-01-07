all:
	g++ server.cpp threadpool.h -o main.out -pthread
	g++ req_generator.cpp -o req_generator.out -pthread
