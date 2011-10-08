/*
 * =====================================================================================
 *
 *       Filename:  Kagent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2011 00:13:26 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "Kagent.h"

using namespace std;

static Kagent* g_instance = NULL;

Kagent::Kagent() {
}

Kagent::~Kagent() {
}

Kagent* Kagent::createKagent(const char* api_name, const char* socket_name, int max_msg_size) {
    return g_instance;
}

void Kagent::destroyKagent(Kagent* kagent) {
    if (g_instance != NULL)
        delete g_instance;
}

int Kagent::joinServer(const char* group, int keylow, int keyhigh) {
    return E_OK;
}

int Kagent::joinClient(const char* group) {
    return E_OK;
}


int Kagent::getErrno() {
    return 0;
}

const char* Kagent::getErrstr() {
    return "undefined";
}
const char* Kagent::getErrstr(int eno) {
    return "undefined";
}

int Kagent::rejoin() {
    return E_OK;
}
void Kagent::leave() {
}

int Kagent::send(const void* buf, int len, int timeout) {
    return E_OK;
}

int Kagent::recv(void* buf, int blen, int timeout) {
    return E_OK;
}

int Kagent::send(const std::string& msg, int timeout) {
    return E_OK;
}

int Kagent::recv(std::string& msg, int timeout) {
    return E_OK;
}

int Kagent::recv(std::string& msg, MsgInfo* info, int timeout) {
    return E_OK;
}

