/*
 * =====================================================================================
 *
 *       Filename:  mthttp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/07/2011 01:45:38 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "mthttp.h"

#include <iostream>

#include <sys/stat.h>
#include <sys/socket.h>
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

using namespace std;

static void handler_cb(struct evhttp_request *req, void *arg);

int main() {
    struct event_base* base = NULL;
    struct evhttp* httpd = NULL;
    struct evhttp_bound_socket* handle;

    unsigned short port = DEFAULT_PORT;

    cout << "start httpd ..." << endl << endl;

    signal(SIGPIPE, SIG_IGN);

    cout << "Create event_base ..." << endl;
    if ((base = event_base_new()) == NULL) {
        cerr << "Error: cannot create an event_base instance" << endl;
        return 1;
    }
    cout << "OK: create event_base" << endl;
    cout << endl;

    cout << "Create evhttp ..." << endl;
    if ((httpd = evhttp_new(base)) == NULL) {
        cerr << "Error: failed to create evhttp" << endl;
        return 1;
    }
    cout << "OK: create evhttp" << endl;
    cout << endl;

    evhttp_set_gencb(httpd, handler_cb, NULL);

    cout << "Bind socket at 0.0.0.0:" << port << endl;
    if ((handle = evhttp_bind_socket_with_handle(httpd, "0.0.0.0", port)) == NULL) {
        cerr << "Error: cannot bind socket at 0.0.0.0:" << port << endl;
        return 1;
    }
    cout << "OK: bind socket" << endl;
    cout << endl;

    cout << "Starting httpd ..." << endl;
    cout << endl;
    event_base_dispatch(base);

    cout << "Done" << endl;
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
