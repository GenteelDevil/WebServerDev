#ifndef LOCKER_H
#define LOCKER_H

#include <pthread.h>
#include <semaphore.h>

#include <exception>

class sem {
   public:
    // 以0为初始值初始化一个信号量
    sem() {
        if (sem_init(&m_sem, 0, 0) != 0) {
            throw std::exception();
        }
    }
    // 以num为初始化初始化一个信号量
    sem(int num) {
        if (sem_init(&m_sem, 0, num) != 0) {
            throw std::exception();
        }
    }
    ~sem() {
        sem_destroy(&m_sem);
    }
    // 封装P操作
    bool wait() {
        return sem_wait(&m_sem) == 0;
    }
    // 封装V操作
    bool post() {
        return sem_post(&m_sem) == 0;
    }

   private:
    // 声明一个信号量
    sem_t m_sem;
};

class locker {
   public:
    locker() {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            throw std::exception();
        }
    }
    ~locker() {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock() {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    bool unlock() {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    pthread_mutex_t *get() {
        return &m_mutex;
    }

   private:
    pthread_mutex_t m_mutex;
};

class cond {
   public:
    cond() {
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            throw std::exception();
        }
    }
    ~cond() {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *m_mutex) {
        int ret = 0;
        ret = pthread_cond_wait(&m_cond, m_mutex);
        return ret == 0;
    }
    // 一直阻塞 直到获得信号 或者最后一个参数指定的时间已经过了
    // 就是指定时间内阻塞
    bool timewait(pthread_mutex_t *m_mutex, struct timespec t) {
        int ret = 0;
        ret = pthread_cond_timedwait(&m_cond, m_mutex, &t);
        return ret == 0;
    }

    bool signal() {
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast() {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

   private:
    pthread_cond_t m_cond;
};

#endif