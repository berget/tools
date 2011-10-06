/*
 * =====================================================================================
 *
 *       Filename:  common.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/07/2011 03:09:39 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "common.h"

static evutil_socket_t bind_socket_ai_(struct evutil_addrinfo* ai, int reuse);

static evutil_addrinfo* make_addrinfo_(const char* address, ev_uint16_t port);

evutil_socket_t bind_socket_(const char* address, ev_uint16_t port, int reuse) {
    evutil_socket_t fd;
    struct evutil_addrinfo *aitop = NULL;

    if (address == NULL && port == 0)
        return bind_socket_ai_(NULL, 0);

    aitop = make_addrinfo_(address, port);

    if (aitop == NULL)
        return -1;

    fd = bind_socket_ai_(aitop, reuse);

    evutil_freeaddrinfo(aitop);

    return fd;
}

evutil_socket_t bind_socket_ai_(struct evutil_addrinfo* ai, int reuse) {
    evutil_socket_t fd;

    int on = 1, r;
    int serrno;

    fd = socket(ai ? ai->ai_family : AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        return -1;

    if (evutil_make_socket_nonblocking(fd) < 0)
        goto out;
    if (evutil_make_socket_closeonexec(fd) < 0)
        goto out;

    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&on, sizeof(on));
    if (reuse)
        evutil_make_listen_socket_reuseable(fd);

    if (ai != NULL) {
        r = bind(fd, ai->ai_addr, (ev_socklen_t)ai->ai_addrlen);
        if (r == -1)
            goto out;
    }
    return (fd);

out:
    serrno = EVUTIL_SOCKET_ERROR();
    evutil_closesocket(fd);
    EVUTIL_SET_SOCKET_ERROR(serrno);
    return -1;
}

evutil_addrinfo* make_addrinfo_(const char* address, ev_uint16_t port) {
    struct evutil_addrinfo *ai = NULL;

    struct evutil_addrinfo hints;
    char strport[NI_MAXSERV];
    int ai_result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    /* turn NULL hostname into INADDR_ANY, and skip looking up any address
     * types we don't have an interface to connect to. */
    hints.ai_flags = EVUTIL_AI_PASSIVE|EVUTIL_AI_ADDRCONFIG;
    evutil_snprintf(strport, sizeof(strport), "%d", port);
    if ((ai_result = evutil_getaddrinfo(address, strport, &hints, &ai))
            != 0) {
        /*
           if (ai_result == EVUTIL_EAI_SYSTEM) {
           event_warn("getaddrinfo");
           } else {
           event_warnx("getaddrinfo: %s",
           evutil_gai_strerror(ai_result));
           }
           */
        return (NULL);
    }

    return (ai);
}
bool sleep_thread(unsigned long timems) {
    struct timespec delta;
    struct timespec remainingSleepTime;
    delta.tv_sec = (int)timems / 1000;
    delta.tv_nsec = (timems % 1000) * 1000000;

    if (nanosleep(&delta, &remainingSleepTime) == -1) {
        //LOGFMT_ERROR("Failed to sleep: (%d, %s)", errno, errorString(errno));
        return false;
    }

    return true;
}
