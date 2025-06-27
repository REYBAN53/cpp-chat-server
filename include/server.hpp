#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <mutex>
#include <algorithm>

#define PORT 9003
#define MAX_CLIENTS 10

void broadcast(const std::string& msg, int sender_fd);
void* handle_client(void* client_socket);
