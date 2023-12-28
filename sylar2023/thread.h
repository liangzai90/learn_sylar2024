#ifndef  __SYLAR_THREAD_H__
#define  __SYLAR_THREAD_H__

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>

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



class RWMutex {
public:
    typedef ReadScopedLockImp<RWMutex> ReadLock;
    typedef WriteScopedLockImp<RWMutex> WriteLock;

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