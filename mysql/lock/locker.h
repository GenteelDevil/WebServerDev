#ifndef LOCKER_H
#define LOCKER_H

#include <pthread.h>
#include <semaphore.h>

#include <exception>

class mem {
   public:
    // 以0为初始值初始化一个信号量
    sem() {
        if (sem_init(&m_sem, 0, 0) != 0) {
            throw std::exception;
        }
    }
    // 以num为初始化初始化一个信号量
    sem(int num) {
        if (sem_init(&m_sem, 0, num) != 0) {
            throw std::exception;
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
#endif