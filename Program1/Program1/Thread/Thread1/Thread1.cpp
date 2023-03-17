#include <algorithm>

#include "Thread1.h"

Thread1::Thread1(std::queue<std::string>* buffer,
                 std::mutex* lock_buffer,
                 std::condition_variable* buffer_check,
                 std::string swap_str,
                 std::size_t max_len) {
    this->buffer = buffer;
    this->lock_buffer = lock_buffer;
    this->buffer_check = buffer_check;

    this->swap_string = swap_str;
    this->max_len = max_len;
};

//Main loop of thread
//Read input from user, handle it and send to Thread2, then read another input from user
void Thread1::Run() {
    while (true) {
        if (!ReadInput()) {
            continue;
        }
        SortInput();
        ReplaceEvenNumbers();
        SendToOtherThread();
    }
}

//Read user input, check it and save input in parameter "input", if it correct
bool Thread1::ReadInput() {
    std::string* str = ReadFromUser();

    if (!CheckOnlyNumbers(*str)) {
        return false;
    }
    if(!CheckLength(*str, this->max_len)) {
        return false;
    }

    this->input = *str;
    delete str;
    return true;
}

//Read user input with lock
std::string* Thread1::ReadFromUser() {
    auto str = new std::string;
    std::cin >> *str;

    return str;
}

bool Thread1::CheckOnlyNumbers(std::string& str) {
    for (char const &ch : str) {
        if (std::isdigit(ch) == 0) {
            return false;
        }
    }
    return true;
}

bool Thread1::CheckLength(std::string& str, std::size_t max_len) {
    return str.length() <= max_len;
}

void Thread1::SortInput() {
    std::sort(this->input.begin(), this->input.end(), [](char a, char b) {
        return a > b;
    });
}

//This function run only with number string, so can get value of each number just subtract '0'
void Thread1::ReplaceEvenNumbers() {
    for (size_t i = 0; i < this->input.length(); i++) {
        if ((this->input[i] - '0') % 2 == 0) {
            this->input.replace(i, 1, this->swap_string);
            i+= this->swap_string.length() - 1;
        }
    }
}

//Start lock, create new buffer to save data to queue and notify other thread
void Thread1::SendToOtherThread() {
    std::unique_lock<std::mutex> locker(*this->lock_buffer);
    this->buffer->push(this->input);
    this->buffer_check->notify_one();
}

Thread1::~Thread1() {};