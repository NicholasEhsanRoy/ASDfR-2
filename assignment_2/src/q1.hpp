#ifndef Q1_HPP
#define Q1_HPP
#include <pthread.h>
#include <time.h>
#include <vector>

namespace Q1 {
class Q1 {
    public:
        Q1();
        ~Q1();
        void join();
        void wait(); 
        static struct timespec exec_time;
        static long run_counter;
        static std::vector<struct timespec> timestamps;
        static float final_answer; 
    private:
        static void* q1_thread(void* arg);
        pthread_t thread;
        static pthread_mutex_t mutex;
};
}
#endif // Q1_HPP


