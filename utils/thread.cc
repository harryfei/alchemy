#include "thread.h"

Thread::Thread(THREAD_CB func)
{
    pid = 0;
    running = false;
    run = func;
}
Thread::~Thread()
{
    join();
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
    t->join();
    t->running_mutex.lock();
    t->beside_run();
    t->running_mutex.unlock();
}
bool Thread::is_running()
{
    bool status = running;
    return status;
}
bool Thread::start()
{
    if(running)
    {
        return true;
    }
    if(pthread_create(&pid,NULL,start_thread,this) != 0)
    {
        return true;
    }
    return false;
}
bool Thread::join()
{
    if(pid != 0)
    {
        return pthread_join(pid,NULL);
    }
    return false;
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
