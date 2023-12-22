#include <iostream>
#include <thread>
#include "../sylar2023/log.h"
#include "../sylar2023/util.h"

int main(int argc, char** argv) {
    //std::cout <<" hello test.cpp "<<std::endl;
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender)); // 给 logger 添加 标准输出流的类


    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    //file_appender->setLevel(sylar::LogLevel::ERROR);
    logger->addAppender(file_appender); // 给logger 添加 写文件的类

    //sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)));
    //event->getSS()<<"Hello  sylar2024 abc"<<std::endl;
    //logger->log(sylar::LogLevel::DEBUG, event);



    // 解释：
    // logger 会遍历appender，这里我们添加了2个appender对象，一个是屏幕输出，一个是文本输出
    // appender的对象会具体输出文本内容
    // 所以，这里logger 打印的日志，会同时出现在 屏幕 和文本文件里面。

    SYLAR_LOG_INFO(logger) << "test macro";
    SYLAR_LOG_ERROR(logger) << "test macro error";

    SYLAR_LOG_FMT_DEBUG(logger, "abcdefghijklmn %d", 12345);
    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    // 这里的manager 只appender 了1个对象，所以只有屏幕输出
    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}
