#include <thread>

#include "Thread2.h"

Thread2::Thread2(std::queue<std::string>* buffer,
                 std::mutex* lock_buffer,
                 std::condition_variable* buffer_check,
                 int port_number) {
    this->buffer = buffer;
    this->lock_buffer = lock_buffer;
    this->buffer_check = buffer_check;
    this->port_number = port_number;

    this->server_messages = new std::queue<int>;

    InitSocket();
};

//Init socket for connection to Program2
void Thread2::InitSocket() {
    this->client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        std::cout << "Error establishing socket..." << std::endl;
        exit(1);
    }

    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(this->port_number);
}

// Create thread that work with Program2 and thread, that handle queue
void Thread2::Run() {
    std::thread server_hand(&Thread2::ServerHandler, this);
    std::thread queue_hand(&Thread2::QueueHandler, this);

    queue_hand.join();
    server_hand.join();
}

void Thread2::QueueHandler() {
    // While handling and sending string to Program2 we can receive more than 1 string from thread1,
    // so here need to use queue for strings and handle it
    while(true) {
        // Wait until thread1 send a notice, that queue is not empty
        std::unique_lock<std::mutex> locker(*this->lock_buffer);
        this->buffer_check->wait(locker);
        // While queue is not empty handle strings
        while (!this->buffer->empty()) {
            // Get local copy of string
            this->buf = this->buffer->front();
            // Delete string from buffer
            this->buffer->pop();
            Output(this->buf);
            int sum = CalculateSumOfNumbers();

            {
                std::unique_lock<std::mutex> locker(this->lock_serv_queue);
                this->server_messages->push(sum);
            }
        }
    }
}

// Maybe should need print not string, so use here template
template <typename T> void Thread2::Output(T& output) {
    std::cout << output << std::endl;
};

int Thread2::CalculateSumOfNumbers() {
    int sum = 0;
    for (char const &ch : this->buf) {
        if (ch >= '0' && ch <= '9') {
            sum += ch - '0';
        }
    }

    return sum;
}

// Thread function, that send info to server. End when thread that listen to server set exit_thread_flag to true
void Thread2::ServerSpeaker() {
    while(!exit_thread_flag) {
        if (!this->server_messages->empty()) {
            int buf_size = 1024;
            char mes_buffer[buf_size];
            this->lock_serv_queue.lock();
            int number = this->server_messages->front();
            this->server_messages->pop();
            this->lock_serv_queue.unlock();
            std::sprintf(mes_buffer, "%d", number);
            send(this->client, mes_buffer, buf_size, 0);
        }
    }
}

// Thread function that listen to server. When server is gone he send FIN => this thread recieve message with 0 length
// and set exit_thread_flag for stop sender thread
void Thread2::ServerListener() {
    int buf_size = 1024;
    char mes_buffer[buf_size];
    int n = recv(this->client, mes_buffer, buf_size, 0);
    if (n == 0) {
        this->exit_thread_flag = true;
    }
}

// Server handler that do connect to server and start two another threads that listen to server and send data to server
// When server is gone two threads are shut down, socket close, initialize new socket and start new thread when connected
// Need to reconnect when server is rebooting
void Thread2::ServerHandler() {
    while(true) {
        if (connect(this->client, (struct sockaddr *) &this->server_addr, sizeof(this->server_addr)) == 0) {
            std::thread listener(&Thread2::ServerListener, this);
            std::thread sender(&Thread2::ServerSpeaker, this);

            listener.join();
            sender.join();

            close(this->client);
            InitSocket();
            this->exit_thread_flag = false;
        }
    }
}

Thread2::~Thread2() {
    delete this->server_messages;
}












