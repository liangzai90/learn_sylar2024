#ifndef  __SYLAR_UTIL_H__
#define  __SYLAR_UTIL_H__

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <vector>
#include <string.h>
#include <string>

namespace sylar{

pid_t GetThreadId();
uint32_t GetFiberId();

void Backtrace(std::vector<std::string>& bt, int size=64, int skip=1);
std::string BacktraceToString(int size = 64, int skip=2, const std::string& prefix="");

}

#endif 