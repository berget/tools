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

#include <sys/stat.h>
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#include <iostream>

#define DEFAULT_PORT 9527

evutil_socket_t bind_socket_(const char* address, ev_uint16_t port, int reuse);

#endif   /* ----- #ifndef COMMON_INC  ----- */
