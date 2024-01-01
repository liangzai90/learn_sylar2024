#include "sylar2023/sylar2023.h"
#include "unistd.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int count = 0;
//sylar::RWMutex s_mutex;
sylar::Mutex s_mutex;

void fun1() {
    SYLAR_LOG_INFO(g_logger) << "name: "<<sylar::Thread::GetName()
                    <<" this.name: "<<sylar::Thread::GetThis()->getName()
                    <<" id: "<<sylar::GetThreadId()
                    <<" this.id:"<<sylar::Thread::GetThis()->getId();
    //sleep(20); //sleep 20 seconds.
    for(int i=0; i<100000; ++i) {
        // sylar::RWMutex::ReadLock lock(s_mutex); // 读锁会不准确
        //sylar::RWMutex::WriteLock lock(s_mutex); // 写锁是正常的
        sylar::Mutex::Lock lock(s_mutex);
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

void test_exception() {
    throw std::logic_error("this is a test exception error 20240101 v1");
    // try{
    //     throw std::logic_error("this is a test exception error20240101 v2");
    // } catch(std::exception& ex) {
    //     std::cout<<"----test---  what:"<< ex.what()<<std::endl;
    // }
}

//! 特别注意：
//! YAML::LoadFile("")这里传入的参数，是日志文件的绝对路径。
//! 如果路径错误了，程序会抛出异常并终止执行。

int main(int argc, char** argv) {
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/henry/workspace/henry-sylar/bin/conf/log2.yml");
    sylar::Config::LoadFromYaml(root);
    //test_exception(); // 我自己写的测试异常的函数
    std::vector<sylar::Thread::ptr> thrs;
    for(int i=0;i<5; i++) {
        //sylar::Thread::ptr thr(new sylar::Thread(&fun1, "name_" + std::to_string(i)));
        sylar::Thread::ptr thr(new sylar::Thread(&fun2, "name_" + std::to_string(i *2)));
        //sylar::Thread::ptr thr2(new sylar::Thread(&fun3, "name_" + std::to_string(i *2 + 1 )));
        thrs.push_back(thr);
        //thrs.push_back(thr2);
    }
   
    for(size_t i=0;i < thrs.size(); ++i) {
        thrs[i]->join();
    }

    SYLAR_LOG_INFO(g_logger) << "thread test end";
    SYLAR_LOG_INFO(g_logger) << "count="<<count;

    return 0;
}