#ifndef ERROR_H
#define ERROR_H

#include <cstdio>
#include <cstdarg>
#include <cstring>

using namespace std;



class Error {
    public:
        Error(const int id, ...);

        int get_id() {return err_id;}
        char* get_msg() {return msg;}

    private:
        int err_id;
        char msg[255];

        const char* msgdesc(const int id);
};


#endif
