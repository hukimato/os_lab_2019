#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
//g++ deadlock.cpp -lpthread -o deadlock.o
int main() {
    std::mutex m1;
    std::mutex m2;
    std::thread t1([&m1, &m2] {
        std::cout << ("1. Acquiring m1.") << std::endl;
        m1.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
         std::cout <<("1. Acquiring m2")<< std::endl;
        m2.lock(); 
    });
    std::thread t2([&m1, &m2] {
         std::cout <<("2. Acquiring m2")<< std::endl;
        m2.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
         std::cout <<("2. Acquiring m1")<< std::endl;
        m1.lock();
    });

    t1.join();
    t2.join();
}
