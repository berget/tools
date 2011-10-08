/*
 * =====================================================================================
 * 
 *       Filename:  Kagent.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  10/08/2011 00:13:31 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Zealot Ke (Zealot), chzealot@gmail.com
 *        Company:  losthit.com
 * 
 * =====================================================================================
 */

#ifndef  KAGENT_INC
#define  KAGENT_INC

#include <string>

struct MsgInfo;

enum
{
    DONTWAIT    = 0,
    WAITFOREVER = -1
};

enum
{
    E_OK,
    E_NULL_HANDLE,
    E_STL_EXCEPTION,
    E_UNKNOWN,
    E_IO,
    E_BUFFER,
    E_TIMEOUT,
    E_ARGUMENT,
    E_RUNTIME,
    E_BADMSG,
};

enum
{
    F_SYNC = 2,
};

class Kagent {
    public:
        Kagent();
        virtual ~Kagent();

        static Kagent* createKagent(const char* api_name, const char* socket_name = NULL, int max_msg_size = 8192);
        static void destroyKagent(Kagent* kagent);

        virtual int joinServer(const char* group, int keylow = -1, int keyhigh = -1) = 0;
        virtual int joinClient(const char* group) = 0;

        virtual int getErrno() = 0;
        virtual const char* getErrstr() = 0;
        virtual const char* getErrstr(int eno) = 0;

        virtual int rejoin() = 0;
        virtual void leave() = 0;

        virtual int send(const void* buf, int len, int timeout = WAITFOREVER) = 0;
        virtual int recv(void* buf, int blen, int timeout = WAITFOREVER) = 0;
        virtual int send(const std::string& msg, int timeout = WAITFOREVER) = 0;
        virtual int recv(std::string& msg, int timeout = WAITFOREVER) = 0;
        virtual int recv(std::string& msg, MsgInfo* info, int timeout = WAITFOREVER) = 0;
};

#endif   /* ----- #ifndef KAGENT_INC  ----- */
