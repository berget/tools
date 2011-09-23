/*
 * =====================================================================================
 *
 *       Filename:  asyncqueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/2011 13:45:30 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "asyncqueue.h"

#include <iostream>

#include <errno.h>
#include <fcntl.h>
using namespace std;

const int AsyncQueue::DEFAULT_SIZE = 1024;

AsyncQueue::AsyncQueue() {
    m_size = AsyncQueue::DEFAULT_SIZE;
    m_sem_empty = SEM_FAILED;
    m_sem_full = SEM_FAILED;
    pthread_mutex_init(&m_mutex, NULL);
}

AsyncQueue::AsyncQueue(const int size) {
    m_size = size;
    m_sem_empty = SEM_FAILED;
    m_sem_full = SEM_FAILED;
    pthread_mutex_init(&m_mutex, NULL);
}

AsyncQueue::~AsyncQueue() {
    clear();

    pthread_mutex_destroy(&m_mutex);

    if (m_sem_empty != SEM_FAILED) {
        sem_close(m_sem_empty);
        sem_unlink("sem_empty1");
    }
    if (m_sem_full != SEM_FAILED) {
        sem_close(m_sem_full);
        sem_unlink("sem_full1");
    }
}

bool AsyncQueue::init() {
    pthread_mutex_init(&m_mutex, NULL);

    m_sem_empty = sem_open("sem_empty1", O_CREAT | O_EXCL, 0644, (unsigned int)m_size);
    if (m_sem_empty == SEM_FAILED) {
        cerr << "sem_open() - sem_empty error(" << errno << "): " << strerror(errno) << endl;
        return false;
    }
    m_sem_full = sem_open("sem_full1", O_CREAT | O_EXCL, 0644, 0);
    if (m_sem_full == SEM_FAILED) {
        cerr << "sem_open() - sem_full error(" << errno << "): " << strerror(errno) << endl;
        return false;
    }
    return true;
}

void AsyncQueue::push(void* item) {
    P(m_sem_empty);

    //pthread_mutex_lock(&m_mutex);
    m_items.push(item);
    //pthread_mutex_unlock(&m_mutex);

    V(m_sem_full);
}

void* AsyncQueue::pop(void) {
    void* result = NULL;

    P(m_sem_full);

    pthread_mutex_lock(&m_mutex);
    if (!m_items.empty()) {
        result = m_items.front();
        m_items.pop();
        V(m_sem_empty);
    }
    pthread_mutex_unlock(&m_mutex);

    return result;
}

void AsyncQueue::clear(void) {
	pthread_mutex_lock(&m_mutex);
    while (!m_items.empty()) {
        m_items.pop();
    }
	pthread_mutex_unlock(&m_mutex);
}

int AsyncQueue::P(sem_t* sem) {
    int ret = -1;

    do {
        ret = sem_wait(sem);
    } while (ret < 0 && errno == EINTR);

    if (ret < 0)
        cerr << "sem_wait() error(" << errno << "): " << strerror(errno) << endl;
    return ret;
}

int AsyncQueue::V(sem_t* sem) {
    int ret = sem_post(sem);

    if (ret < 0)
        cerr << "sem_post() error(" << errno << "): " << strerror(errno) << endl;
    return -1;
}
