#ifndef BUFFER_H
#define BUFFER_H
#include "monitor.h"
#include <queue>
#include <iostream>

const int MAX_BUFFER = 9;
const int MIN_BUFFER = 3;
const int MAX_SUM_A = 20;

extern Semaphore consumers;
extern Semaphore mutex;
extern Semaphore prodA;
extern Semaphore prodB;

extern int line;   //just to make outcome clearer
extern bool A_waits;
extern bool B_waits;


class buffer
{
private:
    std::queue<int> buff;
    unsigned int sum_of_elems;
public:
    buffer();
    int size();
    int sum();
    void push( const int elem );
    int pop();
    int front();

    void consume();
    void produce_A();
    void produce_B();

    ~buffer();
};

#endif // BUFFER_H
