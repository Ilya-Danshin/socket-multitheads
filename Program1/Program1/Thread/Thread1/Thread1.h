#ifndef TEST_THREAD1_H
#define TEST_THREAD1_H

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "../IThread.h"

class Thread1 : public IThread {
public:
    Thread1(std::queue<std::string>* buffer, std::mutex* lock_buffer, std::condition_variable* buffer_check,
            std::string swap_str, std::size_t max_len);
    void Run() override;
    ~Thread1() override;
private:
    std::queue<std::string>* buffer;
    std::mutex* lock_buffer;
    std::condition_variable* buffer_check;
    std::string input;

    std::string swap_string;
    std::size_t max_len;

    bool ReadInput();

    static std::string* ReadFromUser();
    static bool CheckOnlyNumbers(std::string& str);
    static bool CheckLength(std::string& str, std::size_t max_len);

    void SortInput();
    void ReplaceEvenNumbers();
    void SendToOtherThread();
};

#endif //TEST_THREAD1_H
