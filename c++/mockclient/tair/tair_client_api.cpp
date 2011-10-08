/*
 * =====================================================================================
 *
 *       Filename:  tair_client_api.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2011 00:37:50 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 *
 * =====================================================================================
 */
#include "tair_client_api.hpp"

namespace tair {

    tair_client_api::tair_client_api() {
    }

    tair_client_api::~tair_client_api() {
    }

    bool tair_client_api::startup(const char *master_addr,const char *slave_addr,const char *group_name) {
        return true;
    }

    void tair_client_api::set_timeout(int timeout) {
    }

    int tair_client_api::get(int area, const data_entry &key, data_entry*& data) {
        return 1;
    }

    const char *tair_client_api::get_error_msg(int ret) {
        return "undefined";
    }

}
