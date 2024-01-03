#include "../sylar2023/sylar2023.h"
#include <assert.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_assert() {
    /// assert(0); //条件为 false 的时候会出发assert
    SYLAR_LOG_INFO(g_logger) << sylar::BacktraceToString(10);
    SYLAR_ASSERT(false);
    //SYLAR_ASSERT2(false, "aaabbbcccddd");
}

int main(int argc, char** argv) {
    test_assert();


    return 0;
}