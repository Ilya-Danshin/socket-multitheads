#ifndef PROGRAM2_PROGRAM2_H
#define PROGRAM2_PROGRAM2_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>


#include "IProgram2.h"

class Program2 : public IProgram2 {
public:
    explicit Program2(int port_num, int min_data_len, int mul_num);
    void Run() override;
    ~Program2() override;
private:
    int client;
    int server;
    struct sockaddr_in server_addr;
    socklen_t size;

    int min_data_len;
    int mul_num;

    void InitSocket(int port);
    void ListenToClient() const;
    bool CheckData(std::string& data) const;

    template <typename T> static void Output(T& output);
};


#endif //PROGRAM2_PROGRAM2_H
