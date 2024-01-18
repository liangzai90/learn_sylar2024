#include "../sylar2023/hook.h"
#include "../sylar2023/iomanager.h"
#include "../sylar2023/log.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_sleep() {
    sylar::IOManager iom(1);
    iom.schedule([](){
        sleep(2);
        SYLAR_LOG_INFO(g_logger) <<"sleep 2";
    });

    iom.schedule([](){
        sleep(3);
        SYLAR_LOG_INFO(g_logger) <<"sleep 3";
    });

    iom.schedule([](){
        sleep(4);
        SYLAR_LOG_INFO(g_logger) <<"sleep 4";
    });

    SYLAR_LOG_INFO(g_logger) <<"test sleep";
}

void test_sock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "39.156.66.10", &addr.sin_addr.s_addr);

    SYLAR_LOG_INFO(g_logger) <<"begin connect";
    int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
    SYLAR_LOG_INFO(g_logger) << "connect rt="<<rt<<" errno="<<errno;
    if(rt){
        return;
    }

    const char data[] = "GET / HTTP/1.0 \r\n\r\n";
    rt = send(sock, data, sizeof(data), 0);
    SYLAR_LOG_INFO(g_logger)<<"send rt="<<rt<<" errno="<<errno;
    if(rt <= 0) {
        return;
    }

    std::string buff ; // 用到协程，不能分配太大的空间，否则影响效率。。暂时不太理解，先这么注释
    buff.resize(4096);
    rt = recv(sock, &buff[0], buff.size(), 0);
    SYLAR_LOG_INFO(g_logger) << "recv rt="<<rt<<" errno="<<errno;
    if(rt <= 0 ) {
        return;
    }
    buff.resize(rt);
    SYLAR_LOG_INFO(g_logger)<<buff;
}

int main(int argc, char** argv) {
    // test_sleep();
    test_sock();
    return 0;
}