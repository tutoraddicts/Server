#pragma one

#include "util/until.h"
namespace server
{
    void fetchPort(std::string&);
    void initServer(std::string);
    static void eventHandeler(struct mg_connection*, int, void*);
}