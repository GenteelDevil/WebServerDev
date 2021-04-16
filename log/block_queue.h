#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>
// 需要用到基础的锁
#include "../lock/locker.h"
using namespace std;

template <class T>
class block_queue {
   public:
    block_queue(int max_size = 1000) {
        if (max_size <= 0) {
            exit(-1);
        }
        // 阻塞队列的大小、队头、队尾
        m_max_size = max_size;
        m_array = new T[max_size];
        m_size = 0;
        m_front = -1;
        m_back = -1;
    }
    // 定义队列清除
    void clear() {
        m_mutex.lock();
        m_size = 0;
        m_front = -1;
        m_back = -1;
        m_mutex.unlock();
    }
    ~block_queue() {
        // 析构函数清除队列
        m_mutex.lock();
        if (m_array != NULL) {
            delete[] m_array;
        }
        m_mutex.unlock();
    }

    // 判断队列是否满
    bool full() {
        m_mutex.lock();
        if (m_size >= m_maxsize) {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return false;
    }

    // 判断队列是否为空
    bool empty() {
        m_mutex.lock();
        if (m_size == 0) {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return true;
    }

   private:
    locker m_mutex;
    cond m_cond;
    // 定义阻塞队列
    T *m_array;
    int m_size;
    int m_front;
    int m_back;
    int m_maxsize;
};

#endif