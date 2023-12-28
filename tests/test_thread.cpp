#include "sylar2023/sylar2023.h"
#include "unistd.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int count = 0;
sylar::RWMutex s_mutex;

void fun1() {
    SYLAR_LOG_INFO(g_logger) << "name: "<<sylar::Thread::GetName()
                    <<" this.name: "<<sylar::Thread::GetThis()->getName()
                    <<" id: "<<sylar::GetThreadId()
                    <<" this.id:"<<sylar::Thread::GetThis()->getId();
    //sleep(20); //sleep 20 seconds.
    for(int i=0; i<100000; ++i) {
        // sylar::RWMutex::ReadLock lock(s_mutex); // 读锁会不准确
        sylar::RWMutex::WriteLock lock(s_mutex); // 写锁是正常的
        ++count;
    }
}

void fun2() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    std::vector<sylar::Thread::ptr> thrs;
    for(int i=0;i<5; i++) {
        sylar::Thread::ptr thr(new sylar::Thread(&fun1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }
   
    for(int i=0;i < 5; ++i) {
        thrs[i]->join();
    }
    SYLAR_LOG_INFO(g_logger) << "thread test end";
    SYLAR_LOG_INFO(g_logger) << "count="<<count;
    return 0;
}