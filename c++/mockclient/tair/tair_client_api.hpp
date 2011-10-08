/*
 * =====================================================================================
 * 
 *       Filename:  tair_client_api.hpp
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  10/08/2011 00:35:22 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 * 
 * =====================================================================================
 */

#ifndef  TAIR_CLIENT_API_INC
#define  TAIR_CLIENT_API_INC

namespace tair {
    enum {
        TAIR_RETURN_SUCCESS = 0,
        TAIR_RETURN_DATA_NOT_EXIST = 1,
    };

    class data_entry {
        public:
            data_entry() {
            }
            data_entry(const char* p) {
            }
            ~data_entry() {
            }
            char* get_data() const {
                return "undefined";
            }
    };

    class tair_client_api {
        public:
            tair_client_api();
            ~tair_client_api();

            bool startup(const char *master_addr,const char *slave_addr,const char *group_name);

            void set_timeout(int timeout);

            int get(int area, const data_entry &key, data_entry*& data);

            const char *get_error_msg(int ret);
    };

}

#endif   /* ----- #ifndef TAIR_CLIENT_API_INC  ----- */
