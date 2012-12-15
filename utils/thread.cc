#include "thread.h"
#include <stdio.h>

Thread::Thread(THREAD_CB func)
{
    pid = 0;
    running = false;
    run = func;
}

void Thread::beside_run()
{
    running = true;
    run();
    running = false;
}
void *Thread::start_thread(void *thread)
{
    Thread *t = (Thread *)thread;
    t->beside_run();
}
bool Thread::is_running()
{
    return running;
}
bool Thread::start()
{
    if(pthread_create(&pid,NULL,start_thread,this) != 0)
    {
        return true;
    }
    return false;
}
bool Thread::join()
{
    return pthread_join(pid,NULL);
}

Mutex::Mutex()
{
    pthread_mutex_init(&mutex,NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
}

int Mutex::lock()
{
    return pthread_mutex_lock(&mutex);
}

int Mutex::unlock()
{
    return pthread_mutex_unlock(&mutex);
}

int Mutex::trylock()
{
    return pthread_mutex_trylock(&mutex);
}
