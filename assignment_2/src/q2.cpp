
#include <unistd.h> 
// #include <evl/thread.h>
// #include <evl/clock.h>
// #include <evl/sched.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include "q2.hpp"
#include <vector>

namespace Q2 {

    struct timespec Q2::exec_time = {0, 0};
    long Q2:: run_counter = 10000;
    std::vector<struct timespec> Q2::timestamps;
    pthread_mutex_t Q2::mutex = PTHREAD_MUTEX_INITIALIZER;
    float Q2::final_answer = 0.0f;
    void* Q2::q2_thread(void* arg) {
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 1 * 1000 * 1000; 
        int a = 0;
        int b = 0;
        float c = 0.0;
        int i = 1;
        struct timespec start, end;
        int j = 0;
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(1, &cpuset);
        Q2:: timestamps.resize(Q2::run_counter);
        timespec* timePtr = (Q2:: timestamps).data();
        // int efd = evl_attach_self("/q2-evl-%d", getpid());
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
        while (j++ < Q2::run_counter) {

            clock_gettime(CLOCK_MONOTONIC, &start);
            for (i = 1; i < 100; i++) {
                a = i;
                b = i * 10;
                c = i * 2.5;
                final_answer += (a + b) / c;
            }
            // evl_usleep(1000);
            clock_gettime(CLOCK_MONOTONIC, &end);
            timePtr[j-1].tv_nsec = (end.tv_nsec - start.tv_nsec);
            timePtr[j-1].tv_sec = (end.tv_sec - start.tv_sec);
        }
        pthread_mutex_unlock(&(Q2::mutex));
        return nullptr;
    }
    
    Q2::Q2() {
        pthread_mutex_init(&(Q2::mutex), nullptr);
        pthread_mutex_lock(&(Q2::mutex)); 
        pthread_create(&thread, nullptr, q2_thread, nullptr);
    }

    Q2::~Q2() {
        pthread_join(thread, nullptr);
        pthread_mutex_destroy(&mutex);
    }

    void Q2::join() {
        pthread_join(thread, nullptr);
    }

    void Q2::wait(){
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
    }
}
