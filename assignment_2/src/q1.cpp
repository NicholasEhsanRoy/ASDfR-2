#include <pthread.h>
#include <time.h>
#include <iostream>
#include "q1.hpp"
#include <vector>

namespace Q1 {

    struct timespec Q1::exec_time = {0, 0};
    long Q1:: run_counter = 10000;
    std::vector<struct timespec> Q1::timestamps;
    pthread_mutex_t Q1::mutex = PTHREAD_MUTEX_INITIALIZER;
    float Q1::final_answer = 0.0f;
    void* Q1::q1_thread(void* arg) {
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
        CPU_SET(0, &cpuset);
        Q1:: timestamps.resize(Q1::run_counter);
        timespec* timePtr = (Q1:: timestamps).data();
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
        while (j++ < Q1::run_counter) {

            clock_gettime(CLOCK_MONOTONIC, &start);
            for (i = 1; i < 100; i++) {
                a = i;
                b = i * 10;
                c = i * 2.5;
                final_answer += (a + b) / c;
            }
            clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, nullptr);
            clock_gettime(CLOCK_MONOTONIC, &end);
            timePtr[j-1].tv_nsec = (end.tv_nsec - start.tv_nsec);
            timePtr[j-1].tv_sec = (end.tv_sec - start.tv_sec);
        }
        pthread_mutex_unlock(&(Q1::mutex));
        return nullptr;
    }
    
    Q1::Q1() {
        pthread_mutex_init(&(Q1::mutex), nullptr);
        pthread_mutex_lock(&(Q1::mutex)); 
        pthread_create(&thread, nullptr, q1_thread, nullptr);
    }

    Q1::~Q1() {
        pthread_join(thread, nullptr);
        pthread_mutex_destroy(&mutex);
    }

    void Q1::join() {
        pthread_join(thread, nullptr);
    }

    void Q1::wait(){
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
    }
}