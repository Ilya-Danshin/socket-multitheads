#include "Program1.h"

Program1::Program1(std::string swap_string, std::size_t max_len, int port_number) {
    this->buffer = new std::queue<std::string>;
    this->lock_buffer = new std::mutex;
    this->buffer_check = new std::condition_variable;

    this->thr1 = (IThread*) new Thread1(this->buffer, this->lock_buffer, this->buffer_check, swap_string, max_len);
    this->thr2 = (IThread*) new Thread2(this->buffer, this->lock_buffer, this->buffer_check, port_number);
}

void Program1::Run() {
    std::thread t1(&IThread::Run, this->thr1);
    std::thread t2(&IThread::Run, this->thr2);

    t1.join();
    t2.join();
}

Program1::~Program1() {
    delete thr1;
    delete thr2;

    delete buffer;
    delete lock_buffer;
    delete buffer_check;
}

