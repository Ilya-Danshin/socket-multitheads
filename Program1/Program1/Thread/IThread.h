#ifndef TEST_ITHREAD_H
#define TEST_ITHREAD_H

class IThread {
public:
    virtual void Run() = 0;
    virtual ~IThread() = default;
};

#endif //TEST_ITHREAD_H
