#ifndef TEST_THREAD2_H
#define TEST_THREAD2_H

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../IThread.h"

class Thread2 : IThread {
public:
    Thread2(std::queue<std::string>* buffer, std::mutex* lock_buffer, std::condition_variable* buffer_check,
            int port_number);
    void Run() override;
    ~Thread2() override;

private:
    std::queue<std::string>* buffer;
    std::mutex* lock_buffer;
    std::condition_variable* buffer_check;

    std::atomic<bool> exit_thread_flag{false};

    int port_number;
    int client;
    struct sockaddr_in server_addr;

    std::queue<int>* server_messages;
    std::mutex lock_serv_queue;

    std::string buf;

    void InitSocket();
    template <typename T> static void Output(T& output);
    int CalculateSumOfNumbers();

    void QueueHandler();

    void ServerHandler();

    void ServerSpeaker();
    void ServerListener();
};

#endif //TEST_THREAD2_H
