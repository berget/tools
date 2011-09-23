/*
 * =====================================================================================
 * 
 *       Filename:  asyncqueue.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  09/15/2011 13:45:27 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 * 
 * =====================================================================================
 */

#ifndef  ASYNCQUEUE_INC
#define  ASYNCQUEUE_INC

#include <queue>

#include <semaphore.h>
#include <pthread.h>

class AsyncQueue {
public:
    AsyncQueue();
    AsyncQueue(const int size);
    ~AsyncQueue();

    bool init(void);

    void push(void *item);
    void* pop(void);

    void clear();

    static const int DEFAULT_SIZE;

private:
    int m_size;
    pthread_mutex_t m_mutex;

    sem_t* m_sem_empty;
    sem_t* m_sem_full;

    std::queue<void*> m_items;

    int P(sem_t*);
    int V(sem_t*);
};

#endif   /* ----- #ifndef ASYNCQUEUE_INC  ----- */
