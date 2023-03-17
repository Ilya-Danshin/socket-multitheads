#ifndef TEST_PROGRAM1_H
#define TEST_PROGRAM1_H

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

#include "IProgram1.h"
#include "Thread/IThread.h"
#include "Thread/Thread1/Thread1.h"
#include "Thread/Thread2/Thread2.h"

class Program1 : public IProgram1 {
public:
    Program1(std::string swap_string, std::size_t max_len, int port_number);
    void Run() override;
    ~Program1();
private:
    IThread* thr1;
    IThread* thr2;

    std::queue<std::string>* buffer;
    std::mutex* lock_buffer;
    std::condition_variable* buffer_check;

};


#endif //TEST_PROGRAM1_H
