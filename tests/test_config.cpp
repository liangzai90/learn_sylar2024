#include "../sylar2023/config.h"
#include "../sylar2023/log.h"

sylar::ConfigVar<int>::ptr g_int_value_config = 
    sylar::Config::Lookup("system.port", (int)8080, "system port");
sylar::ConfigVar<float>::ptr g_float_value_config = 
    sylar::Config::Lookup("system.value", (float)3.1415, "system value");

int main(){

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<g_int_value_config->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<g_float_value_config->toString();

    return 0;
}
