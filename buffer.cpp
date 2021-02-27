#include "buffer.h"
#include <time.h>

Semaphore consumers(0);
Semaphore mutex(1);
Semaphore prodA(0);
Semaphore prodB(0);

int line = 1;
bool A_waits = false;
bool B_waits = false;

buffer::buffer(){}
buffer::~buffer(){}

int buffer::size()
{
    return buff.size();
}

int buffer::sum()
{
    return sum_of_elems;
}

int buffer::front()
{
    return buff.front();
}

void buffer::push( const int elem )
{
    buff.push( elem );
    sum_of_elems += elem;
}

int buffer::pop()
{
    int tmp = buff.front();
    sum_of_elems -= tmp;
    buff.pop();
    return tmp;
}

void buffer::produce_A()
{
    mutex.p();
    if( !(sum() < MAX_SUM_A && size() < MAX_BUFFER) )
    {
        std::cout << line << ": " << "Prod A zawiesil sie " << std::endl; ++line;
        A_waits = true;
        mutex.v();
        prodA.p();
        A_waits = false;
    }
    push( rand() % 10 + 1 );
    std::cout << line << ": " << "Producent A dodal nowy element:  " << front() << std::endl; ++line;
        //std::cout << line << ": " << "Rozmiar bufora po produkcji: " << size() << std::endl; ++line;
        //std::cout << line << ": " << "Suma suma elementow w buforze po produkcji: " << sum() << std::endl; ++line;

    if( size() > MIN_BUFFER )
    {
            //std::cout << line << ": " << "Prod A wznowil konsumentow " << std::endl; ++line;
        consumers.v();
    }
        //std::cout << line << ": " << "Prod A zwolnil SK " << std::endl; ++line;
    mutex.v();
}

void buffer::produce_B()
{
    mutex.p();
    if( !(size() < MAX_BUFFER) ){
            //std::cout << line << ": " << "Prod B zawiesil sie " << std::endl; ++line;
        B_waits = true;
        mutex.v();
        prodB.p();
        B_waits = false;
    }
    push( rand() % 10 + 1 );
    std::cout << line << ": " << "Producent B dodal nowy element: "<< front() << std::endl; ++line;
        //std::cout << line << ": " << "Rozmiar bufora po produkcji: " << size() << std::endl; ++line;
        //std::cout << line << ": " << "Suma suma elementow w buforze po produkcji: " << sum() << std::endl; ++line;

    if( size() > MIN_BUFFER ){
            //std::cout << line << ": " << "Prod B wznowil konsumentow " << std::endl; ++line;
        consumers.v();
    }
        //std::cout << line << ": " << "Prod B zwolnil SK " << std::endl; ++line;
    mutex.v();
}

void buffer::consume()
{
    consumers.p();
    mutex.p();

        std::cout << line << ": " << "Konsument usunal element: " << pop() << std::endl; ++line;
            //std::cout << line << ": " << "Rozmiar bufora po konsumpcji: " << size() << std::endl; ++line;
            //std::cout << line << ": " << "Suma suma elementow w buforze po konsumpcji: " << sum() << std::endl; ++line;

        if( A_waits && sum() < MAX_SUM_A && size() < MAX_BUFFER ){
                    //std::cout << line << ": " << "Kons wznowil Prod A " << std::endl; ++line;
                A_waits = false;
                prodA.v();
        }
        else{
            if( B_waits && size() < MAX_BUFFER ){
                    //std::cout << line << ": " << "Kons wznowil Prod B " << std::endl; ++line;
                prodB.v();
            }
            else{
                    //std::cout << line << ": " << "Kons nie wznowil nikogo i wyszedl z SK " << std::endl; ++line;
                mutex.v();
            }
        }
}
