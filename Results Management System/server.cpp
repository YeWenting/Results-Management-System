//
//  server.cpp
//  Results Management System
//
//  Created by YeWenting. on 16/6/15.
//  Copyright © 2016年 School of Computer Science. All rights reserved.
//
#define PORT 1234

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "csapp.h"

int main(){
    //创建套接字
    int serv_sock = open_listenfd(PORT);
    
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    
    char str[] = "Hello World!";
    write(clnt_sock, str, sizeof(str));
    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}


//#include <sys/time.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <sys/ioctl.h>
//#include <netdb.h>
//#include <thread>
//
//bool isclosed(int sock) {
//    fd_set rfd;
//    FD_ZERO(&rfd);
//    FD_SET(sock, &rfd);
//    timeval tv = { 0 };
//    select(sock+1, &rfd, 0, 0, &tv);    //判断fd状态是否可读
//    if (!FD_ISSET(sock, &rfd))
//        return false;
//    int n = 0;
//    ioctl(sock, FIONREAD, &n);          //判断fd还有东西读吗
//    return n == 0;
//}
//
//int make_accept_sock (const char *servspec) {
//    const int one = 1;
//    struct addrinfo hints = {};
//    struct addrinfo *res = 0, *ai = 0, *ai4 = 0;
//    char *node = strdup(servspec);
//    char *service = strrchr(node, ':');
//    int sock;
//
//    hints.ai_family = PF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_flags = AI_PASSIVE;
//
//    *service++ = '\0';
//    getaddrinfo(*node ? node : "0::0", service, &hints, &res);
//    free(node);
//
//    for (ai = res; ai; ai = ai->ai_next) {
//        if (ai->ai_family == PF_INET6) break;
//        else if (ai->ai_family == PF_INET) ai4 = ai;
//    }
//    ai = ai ? ai : ai4;
//
//    sock = socket(ai->ai_family, SOCK_STREAM, 0);
//    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
//    bind(sock, ai->ai_addr, ai->ai_addrlen);
//    listen(sock, 256);
//    freeaddrinfo(res);
//
//    return sock;
//}
//
//void new_connection (int sock) {
//    ssize_t r;
//    while (!isclosed(sock)) {
//        r = send(sock, ".\n", 2, 0);
//        if (r < 0) break;
//        sleep(1);
//    }
//    close(sock);
//}
//
//void accept_loop (const char *servspec) {
//    int sock = make_accept_sock(servspec);
//
//    for (;;) {
//        int new_sock = accept(sock, 0, 0);
//        std::thread t(new_connection, new_sock);
//        t.detach();
//    }
//}
////
//#include <cstdlib>
//#include <iostream>
//#include <boost/bind.hpp>
//#include <boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//
//class session
//{
//public:
//    session(boost::asio::io_service& io_service)
//    : socket_(io_service)
//    {
//    }
//
//    tcp::socket& socket()
//    {
//        return socket_;
//    }
//
//    void start()
//    {
//        socket_.async_read_some(boost::asio::buffer(data_, max_length),
//                                boost::bind(&session::handle_read, this,
//                                            boost::asio::placeholders::error,
//                                            boost::asio::placeholders::bytes_transferred));
//    }
//
//private:
//    void handle_read(const boost::system::error_code& error,
//                     size_t bytes_transferred)
//    {
//        if (!error)
//        {
//            boost::asio::async_write(socket_,
//                                     boost::asio::buffer(data_, bytes_transferred),
//                                     boost::bind(&session::handle_write, this,
//                                                 boost::asio::placeholders::error));
//        }
//        else
//        {
//            delete this;
//        }
//    }
//
//    void handle_write(const boost::system::error_code& error)
//    {
//        if (!error)
//        {
//            socket_.async_read_some(boost::asio::buffer(data_, max_length),
//                                    boost::bind(&session::handle_read, this,
//                                                boost::asio::placeholders::error,
//                                                boost::asio::placeholders::bytes_transferred));
//        }
//        else
//        {
//            delete this;
//        }
//    }
//
//    tcp::socket socket_;
//    enum { max_length = 1024 };
//    char data_[max_length];
//};
//
//class server
//{
//public:
//    server(boost::asio::io_service& io_service, short port)
//    : io_service_(io_service),
//    acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
//    {
//        start_accept();
//    }
//
//private:
//    void start_accept()
//    {
//        session* new_session = new session(io_service_);
//        acceptor_.async_accept(new_session->socket(),
//                               boost::bind(&server::handle_accept, this, new_session,
//                                           boost::asio::placeholders::error));
//    }
//
//    void handle_accept(session* new_session,
//                       const boost::system::error_code& error)
//    {
//        if (!error)
//        {
//            new_session->start();
//        }
//        else
//        {
//            delete new_session;
//        }
//
//        start_accept();
//    }
//
//    boost::asio::io_service& io_service_;
//    tcp::acceptor acceptor_;
//};
//
//int main(int argc, char* argv[])
//{
//    try
//    {
//        if (argc != 2)
//        {
//            std::cerr << "Usage: async_tcp_echo_server <port>\n";
//            return 1;
//        }
//
//        boost::asio::io_service io_service;
//
//        using namespace std; // For atoi.
//        server s(io_service, atoi(argv[1]));
//
//        io_service.run();
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}