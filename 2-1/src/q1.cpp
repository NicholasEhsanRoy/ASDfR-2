#include "q1.hpp"
#include <pthread.h>

namespace Q1 {
    Q1::Q1() {
        pthread_t thread;
        pthread_create(&thread, nullptr, q1_thread, nullptr);
        pthread_detach(thread); 
    }

    static void* q1_thread(void* arg) {
        return nullptr;
    }
}
