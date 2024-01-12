#include "../sylar2023/sylar2023.h"
#include "../sylar2023/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int sock = 0;

void test_fiber() {
    SYLAR_LOG_INFO(g_logger)<<"test_fiber sock="<<sock;

    sleep(3);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "58.254.137.162", &addr.sin_addr.s_addr);

    if(!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
    } else if(errno == EINPROGRESS) {
        SYLAR_LOG_INFO(g_logger) <<"add event error="<<errno<<" "<<strerror(errno);
        sylar::IOManager::GetThis()->addEvent(sock, sylar::IOManager::READ, [](){
            SYLAR_LOG_INFO(g_logger) << "read callback";
        });
        sylar::IOManager::GetThis()->addEvent(sock, sylar::IOManager::WRITE, [](){
            SYLAR_LOG_INFO(g_logger) << "write callback";
            sylar::IOManager::GetThis()->cancelEvent(sock, sylar::IOManager::READ);
            close(sock);
        });
    } else {
        SYLAR_LOG_INFO(g_logger) <<"else "<<errno<<" "<<strerror(errno);
    }
}

void test1() {
    std::cout<<"EPOLLIN="<<EPOLLIN
            <<" EPOLLOUT="<<EPOLLOUT<<std::endl;
    sylar::IOManager  iom(2, false);
    iom.schedule(&test_fiber);
}

void test_timer() {
    sylar::IOManager iom(2);
    iom.addTimer(500,[](){
        SYLAR_LOG_INFO(g_logger)<<" hello timer ";
    }, true);
}

sylar::Timer::ptr s_timer;
void test_timer2() {
    sylar::IOManager iom(2);
    s_timer = iom.addTimer(1000,[](){
        static int i=0;
        SYLAR_LOG_INFO(g_logger)<<" hello timer i="<<i;
        if(++i == 5) {
            s_timer->cancel();
        }
    }, true);
}

int main(int argc, char** argv) {
    //test1();
    //test_timer();
    test_timer2();
    return 0;
}
