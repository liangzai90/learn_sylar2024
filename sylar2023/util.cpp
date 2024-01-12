#include "util.h"
#include <execinfo.h>
#include "fiber.h"
#include <iostream>
#include "log.h"
#include <sys/time.h>

namespace sylar{

sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}

uint32_t GetFiberId(){
    return sylar::Fiber::GetFiberId();
}

// 这里是用的协程，资源利用要到极致
// 尽量不要在栈上面分配较大的内容。可以通过传递指针的方式传入参数
// 比如，定义一个临时变量或者数组，就是在栈上分配内存了
void Backtrace(std::vector<std::string>& bt, int size, int skip) {
    void** array = (void**)malloc((sizeof(void*) * size));
    std::cout<<"size:"<<size<<", sizeof(void*):"<< sizeof(void*)<<std::endl;
    size_t s = ::backtrace(array, size);

    char** strings = backtrace_symbols(array, s);
    if(strings == NULL) {
        SYLAR_LOG_ERROR(g_logger) <<"backtrace_synbols error";
        return ;
    }

    for(size_t i=skip; i<s; ++i)  {
        bt.push_back(strings[i]);
    }

    free(strings);
    free(array);
}

std::string BacktraceToString(int size, int skip, const std::string& prefix) {
    std::vector<std::string> bt;
    Backtrace(bt, size, skip);
    std::stringstream ss;
    for(size_t i = 0; i<bt.size();++i) {
        ss<<prefix<<bt[i]<<std::endl;
    }
    return ss.str();
}

uint64_t GetCurrentMS() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000ul + tv.tv_usec / 1000;
}

uint64_t GetCurrentUS() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 * 1000ul + tv.tv_usec;
}

}
