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

    void clear() {
        }
};

#endif