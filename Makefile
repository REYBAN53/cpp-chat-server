all:
	g++ -std=c++11 src/server.cpp -o build/chatserver -pthread