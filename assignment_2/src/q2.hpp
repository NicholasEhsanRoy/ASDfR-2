#ifndef Q2_HPP
#define Q2_HPP
#include <pthread.h>
#include <time.h>
#include <vector>

namespace Q2 {
class Q2 {
    public:
        Q2();
        ~Q2();
        void join();
        void wait(); 
        static struct timespec exec_time;
        static long run_counter;
        static std::vector<struct timespec> timestamps;
        static float final_answer; 
    private:
        static void* q2_thread(void* arg);
        pthread_t thread;
        static pthread_mutex_t mutex;
};
}
#endif //Q2_HPP

// g++ main.cpp q2.cpp -o main $(pkg-config /usr/evl/lib/pkgconfig/evl.pc --cflags --libs)