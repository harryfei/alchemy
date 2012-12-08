#ifndef THREAD_H_H_H
#define THREAD_H_H_H
#include <pthread.h>
#include "delegate_tmpl.h"

typedef Func0<void> THREAD_CB;
class Thread
{
    private:
        pthread_t pid;
        THREAD_CB run;
        static void *start_thread(void *runner);
        bool running;
    public:
        void beside_run();
        Thread(THREAD_CB func);
        bool start();
        bool is_running();
};

#endif
