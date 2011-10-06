/*
 * =====================================================================================
 * 
 *       Filename:  common.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  10/07/2011 03:09:36 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 * 
 * =====================================================================================
 */

#ifndef  COMMON_INC
#define  COMMON_INC

#include <iostream>

#include <sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#define DEFAULT_PORT    9527
#define THREAD_NUMBER   12

struct thread_body {
    pthread_t tid;
    evutil_socket_t listen_fd;
    size_t index;
};

/* just like bind_socket() in libevent */
evutil_socket_t bind_socket_(const char* address, ev_uint16_t port, int reuse);

bool sleep_thread(unsigned long timems);

#endif   /* ----- #ifndef COMMON_INC  ----- */
