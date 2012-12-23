#ifndef THREAD_H_H_H
#define THREAD_H_H_H
#include <pthread.h>
#include "delegate_tmpl.h"

class Mutex
{
    public:
        Mutex();
        ~Mutex();
        int lock();
        int unlock();
        int trylock();
    private:
        pthread_mutex_t mutex;

};

typedef Func0<void> THREAD_CB;
class Thread
{
    private:
        pthread_t pid;
        THREAD_CB run;
        static void *start_thread(void *runner);
        bool running;
    public:
        Mutex running_mutex;
        void beside_run();
        Thread(THREAD_CB func);
        ~Thread();
        bool start();
        bool is_running();
        bool join();
};

#endif
