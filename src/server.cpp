#include "../include/server.hpp"

std::vector<int> clients;
std::mutex clients_mutex;

void broadcast(const std::string& msg, int sender_fd) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (int client_fd : clients) {
        if (client_fd != sender_fd) {
            send(client_fd, msg.c_str(), msg.length(), 0);
        }
    }
}

void* handle_client(void* client_socket) {
    int client_fd = *(int*)client_socket;
    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cerr << "Client disconnected: " << client_fd << std::endl;
            close(client_fd);
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
            break;
        }
        std::string message = "Client " + std::to_string(client_fd) + ": " + buffer;
        std::cout << message;
        broadcast(message, client_fd);
    }
    return nullptr;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return -1;
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }

    std::cout << "Chat server started on port " << PORT << std::endl;

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Failed to accept connection." << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.push_back(client_fd);

        pthread_t thread_id;
        pthread_create(&thread_id, nullptr, handle_client, (void*)&client_fd);
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
