#include "Program2.h"

Program2::Program2(int port_num, int min_data_len, int mul_num) {
    this->min_data_len = min_data_len;
    this->mul_num = mul_num;

    InitSocket(port_num);
}

void Program2::InitSocket(int port) {
    this->client = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client < 0)
    {
        std::cout << "Error  establishing socket..." << std::endl;
        exit(1);
    }

    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    this->server_addr.sin_port = htons(port);

    if ((bind(this->client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    {
        std::cout << "Error binding connection, the socket has already been established..." << std::endl;
        exit(1);
    }

    this->size = sizeof(server_addr);
}

// Main loop, start listen and then endless loop for accept connection.
void Program2::Run() {
    listen(this->client, 1);
    while (true) {
        this->server = accept(this->client, (struct sockaddr *) &this->server_addr, &this->size);
        if (server < 0) {
            std::cout << "Error on accepting..." << std::endl;
            continue;
        }
        ListenToClient();
    }
}

// Handle of client
void Program2::ListenToClient() const {
    int buf_size = 1024;
    char buffer[buf_size];

    while (true) {
        size_t n = recv(this->server, buffer, buf_size, 0);
        if (n == 0) { // End of connection
            break;
        }
        std::string str(buffer);
        if (CheckData(str)) {
            Output("Get data");
        } else {
            Output("Error: get incorrect data");
        }
    }
}

bool Program2::CheckData(std::string& data) const {
    if ((data.length() > this->min_data_len) && (std::stoi(data) % this->mul_num == 0)) {
        return true;
    }
    return false;
}

template<typename T>
void Program2::Output(T &output) {
    std::cout << output << std::endl;
}

Program2::~Program2() {

}








