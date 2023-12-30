#ifndef  __SYLAR_THREAD_H__
#define  __SYLAR_THREAD_H__

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <atomic>

namespace sylar{

class Semaphore {
public:
    Semaphore(uint32_t count = 0); 
    ~Semaphore();

    void wait();
    void notify();
/*
这里使用了 C++11 的 delete 关键字
来删除拷贝构造函数、移动构造函数和拷贝赋值运算符。
这是为了禁止复制和移动操作，
表明这个类不允许被拷贝或移动，从而确保在使用时不会出现意外的行为。
*/    
private:
    Semaphore(const Semaphore& ) = delete; //拷贝构造
    Semaphore(const Semaphore&& ) = delete; //移动构造
    Semaphore& operator=(const Semaphore& ) = delete;//拷贝复制运算符
private:
    sem_t m_semaphore;
};    

template<class T>
class ScopedLockImp {
public:
    ScopedLockImp(T& mutex) 
        :m_mutex(mutex) {
        m_mutex.lock();
        m_locked = true;
    }

    ~ScopedLockImp() {
        unlock();
    }

    void lock() {
        if(!m_locked) {
            m_mutex.lock();
            m_locked = true;
        }
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked;    
};

template<class T>
class ReadScopedLockImp {
public:
    ReadScopedLockImp(T& mutex) 
        :m_mutex(mutex) {
        m_mutex.rdlock();
        m_locked = true;
    }

    ~ReadScopedLockImp() {
        unlock();
    }

    void lock() {
        if(!m_locked) {
            m_mutex.rdlock();
            m_locked = true;
        }
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked;    
};


template<class T>
class WriteScopedLockImp {
public:
    WriteScopedLockImp(T& mutex) 
        :m_mutex(mutex) {
        m_mutex.wrlock();
        m_locked = true;
    }

    ~WriteScopedLockImp() {
        unlock();
    }

    void lock() {
        if(!m_locked) {
            m_mutex.wrlock();
            m_locked = true;
        }
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked;    
};

class Mutex {
public:
    typedef ScopedLockImp<Mutex> Lock;
    Mutex() {
        pthread_mutex_init(&m_mutex, nullptr);
    }  
    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};

class NullMutex {
public:
    typedef ScopedLockImp<Mutex> Lock;
    NullMutex() {}  
    ~NullMutex() {}
    void lock() {}
    void unlock() {}
private:
    pthread_mutex_t m_mutex;
};


class RWMutex {
public:
//在这个特定的代码中，不会发生模板循环。
//原因是这两个别名的定义是在 RWMutex 类的内部进行的，而不是在模板实例化的过程中。
    typedef ReadScopedLockImp<RWMutex> ReadLock;  // readLock 模板别名
    typedef WriteScopedLockImp<RWMutex> WriteLock; // writeLock 模板别名

    RWMutex() {
        pthread_rwlock_init(&m_lock, nullptr);
    }
    ~RWMutex() {
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock() {
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock() {
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock() {
        pthread_rwlock_unlock(&m_lock);
    }
private:
    pthread_rwlock_t m_lock;
};

//定义NullRWMutex 是为了以后测试 锁的功能的
class NullRWMutex {
public:
    typedef ReadScopedLockImp<NullRWMutex> ReadLock; 
    typedef WriteScopedLockImp<NullRWMutex> WriteLock; 

    NullRWMutex() {}
    ~NullRWMutex() {}
    void rdlock() {}
    void wrlock() {}
    void unlock() {}
private:
     pthread_rwlock_t m_lock;
};

class Spinlock {
public:
    typedef ScopedLockImp<Spinlock> Lock;
    Spinlock() {
        pthread_spin_init(&m_mutex, 0);
    }
    ~Spinlock() {
        pthread_spin_destroy(&m_mutex);
    }
    void lock() {
        pthread_spin_lock(&m_mutex);
    }
    void unlock() {
        pthread_spin_unlock(&m_mutex);
    }
private:
    pthread_spinlock_t m_mutex;
};

class CASLock {
public:
    typedef ScopedLockImp<CASLock> Lock;
    CASLock() {
        m_mutex.clear();
    }
    ~CASLock() {
    }
    void lock() {
        while(std::atomic_flag_test_and_set_explicit(&m_mutex, std::memory_order_acquire));
    }
    void unlock() {
        std::atomic_flag_clear_explicit(&m_mutex, std::memory_order_release);
    }
private:
    volatile std::atomic_flag m_mutex;    
};

class Thread {
public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, const std::string& name);
    ~Thread();

    pid_t getId() const { return m_id;}
    const std::string& getName() const {return m_name;}
    void join();

    static Thread* GetThis();
    static const std::string& GetName();
    static void SetName(const std::string& name);
private:
    Thread(const Thread&) = delete;
    Thread(const Thread&&) = delete; 
    Thread& operator=(const Thread&) = delete; 

    static void* run(void* arg);
private:
    pid_t m_id = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;
    Semaphore m_semaphore;
};


}
#endif