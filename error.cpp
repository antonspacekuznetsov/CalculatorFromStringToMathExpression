#include "error.h"

using namespace std;

Error::Error(const int id, ...)
:err_id(id)
{

    const char* msg_desc = msgdesc(id);

    va_list args;
    va_start(args, msg_desc);
    vsnprintf(msg, sizeof(msg)-1, msg_desc, args);
    msg[sizeof(msg)-1] = '\0';
    va_end(args);
}

const char* Error::msgdesc(const int id)
{
    switch (id)
    {
        case 1: return "Syntax error in part \"%s\"";
        case 2: return "Syntax error";
        case 3: return "Parentesis ) missing";
        case 4: return "Empty expression";
        case 5: return "Unexpected part \"%s\"";
        case 6: return "Unexpected end of expression";
        case 7: return "Value expected";
        case 101: return "Unknown operator %s";
        case 200: return "Too long expression, maximum number of characters exceeded";

    }

    return "Unknown error";
}
