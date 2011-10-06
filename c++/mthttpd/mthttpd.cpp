/*
 * =====================================================================================
 *
 *       Filename:  mthttpd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/07/2011 03:25:09 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */

#include "common.h"

using namespace std;

static void handler_cb(struct evhttp_request *req, void *arg);

static void* start_httpd(void* arg);

int main(int argc, char** argv) {
    unsigned short port = DEFAULT_PORT;
    if (argc >= 2)
        port = (unsigned short)atoi(argv[1]);

    signal(SIGPIPE, SIG_IGN);

    cout << "Bind socket at 0.0.0.0:" << port << endl;
    evutil_socket_t fd;
    if ((fd = bind_socket_("0.0.0.0", port, 1 /*reuse*/)) == -1) {
        cerr << "Error: Failed to Bind socket" << endl;
        return -1;
    }
    cout << "OK: bind socket" << endl;
    cout << endl;

    cout << "listen socket ..." << endl;
    if (listen(fd, 128) == -1) {
        cerr << "Error: Failed to listen socket" << endl;
        evutil_closesocket(fd);
        return -1;
    }
    cout << "OK: listen socket" << endl;
    cout << endl;

    struct thread_body thread_pool[THREAD_NUMBER];

    for (size_t i = 0; i < THREAD_NUMBER; ++i) {
        thread_pool[i].tid = 0;
        thread_pool[i].index = i;
        thread_pool[i].listen_fd = fd;
    }
    for (size_t i = 0; i < THREAD_NUMBER; ++i) {
        pthread_create(&thread_pool[i].tid, NULL, start_httpd, &thread_pool[i]);
    }

    void* tret;
    for (size_t i = 0; i < THREAD_NUMBER; ++i) {
        pthread_join(thread_pool[i].tid, &tret);
    }

    return 0;
}

void handler_cb(struct evhttp_request *req, void *arg) {
    const char* cmdtype = "UNKNOWN";
    struct evkeyvalq* headers = NULL;
    struct evkeyval* header = NULL;
    struct evbuffer* buf = NULL;

    buf = evbuffer_new();

    evbuffer_add_printf(buf, "Hello World!\n\n");
    time_t clock = time(NULL);
    char strBuffer[32] = {0};
    ctime_r(&clock, strBuffer);
    evbuffer_add_printf(buf, "time is %s\n\n", strBuffer);
    evbuffer_add_printf(buf, "arg is %p\n\n", arg);
    evbuffer_add_printf(buf, "Dump Headers\n");

    switch (evhttp_request_get_command(req)) {
        case EVHTTP_REQ_GET: cmdtype = "GET"; break;
        case EVHTTP_REQ_POST: cmdtype = "POST"; break;
        case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
        case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
        case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
        case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
        case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
        case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
        case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
        default: cmdtype = "unknown"; break;
    }
    cout << "Received a \"" << cmdtype << "\" request for \"" << evhttp_request_get_uri(req) << "\"" << endl;
    cout << "Header: \n";
    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header; header = header->next.tqe_next) {
        cout << "  " << header->key << ": " << header->value << endl;
        evbuffer_add_printf(buf, "- %s: %s\n", header->key, header->value);
    }

    evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/plain");

    evhttp_send_reply(req, 200, "OK", buf);

    if (buf)
        evbuffer_free(buf);
    return;
}

void* start_httpd(void* arg) {
    struct thread_body* body = (struct thread_body*)arg;
    evutil_socket_t fd = body->listen_fd;

    printf("start httpd: %lu, tid=%lu, at address: %p\n", body->index, (unsigned long)body->tid, body);

    struct event_base* base = NULL;
    struct evhttp* httpd = NULL;

    cout << "Create event_base ..." << endl;
    if ((base = event_base_new()) == NULL) {
        cerr << "Error: cannot create an event_base instance" << endl;
        return NULL;
    }
    cout << "OK: create event_base" << endl;
    cout << endl;

    cout << "Create evhttp ..." << endl;
    if ((httpd = evhttp_new(base)) == NULL) {
        cerr << "Error: failed to create evhttp" << endl;
        return NULL;
    }
    cout << "OK: create evhttp" << endl;
    cout << endl;

    evhttp_set_gencb(httpd, handler_cb, NULL);

    cout << "Accept socket ..." << endl;
    if (evhttp_accept_socket(httpd, fd) == -1) {
        cerr << "Error: cannot accept socket"<< endl;
        return NULL;
    }
    cout << "OK: accept socket" << endl;
    cout << endl;

    cout << "Starting httpd ..." << endl;
    cout << endl;
    event_base_dispatch(base);

    return NULL;
}
