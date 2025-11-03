#include <iostream>
#include <mutex>
#include <string>
#include <thread>

/* 
Singleton - a way to organize global data with functions which act on that data.
Ensures only one instance exists (Meyers’ Singleton, thread-safe since C++11).

Suitable for:
 - random number generator,
 - logger,
 - manager of resources.
*/

class Logger
{
public:
    static Logger& getInstance() {
        static Logger instance{}; /* thread-safe initialization */

        return instance;
    }

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);

        std::cout<<msg<<'\n';
    }

private:
    Logger()  = default;
    ~Logger() = default;

    std::mutex mutex_;

    Logger(const Logger& other)            = delete;
    Logger& operator=(const Logger& other) = delete;
    Logger(Logger&& other)                 = delete;
    Logger& operator=(Logger&& other)      = delete;
};


void task(int id)
{
    for(int i : {1, 2, 3, 4, 5})
    {
        Logger::getInstance().log("Thread of id: " + std::to_string(id) + ", iteration of log: " + std::to_string(i));
    }
}

int main()
{
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();
}