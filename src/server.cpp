/*
* Simple Programe to creat server in any port using mongoose - link :- https://github.com/cesanta/mongoose
* where you pass the port number during execution or in runtime
* int main the main funtion /- where the programe startes when we execute the programe
*/

#include <iostream>
#include <string>
#include <future>

#include "server.h"
#include "util/until.h"

static struct mg_serve_http_opts server_opts; // struct for mongoose which contain settings for mongoose
static std::string quit;
static std::atomic_bool stop = false;

void server::fetchPort(std::string &port)
{
    // char default = 'd';
    //std::cin.ignore();
    std::cout << "Enter Your Server Port (for default port type -d): " ; 
    std::cin >> port;

    if (std::cin.fail() || port == "-d")
        port = "4400"; // by default we are settings the port to 4400 IF the user did not enter any port then we will continue with 4400
}

static void server::eventHandeler(struct mg_connection *mc, int event, void *p)
{
    // If evenet is a http request
    if (event == MG_EV_HTTP_REQUEST)
    {
        // Server Static files
        mg_serve_http(mc, (struct http_message *)p, server_opts);
    }
}

/*
* This Method is to initialise the server
*/
void server::initServer(std::string port)
{  
    // Mongoose Event Manager
    struct mg_mgr mgr;
    // Mongoose Connection
    struct mg_connection *mc;

    // inisialisng mongoose
    mg_mgr_init(&mgr, NULL);

    mc = mg_bind(&mgr, ConvertDataType::StringToChar(port), server::eventHandeler);
    
    // std::cout << "in mc done" << std::endl;
    if (mc == NULL) // cheking if the server is actually created or not if not it will return 1
    {
        std::cout << "failed to create the server" << std::endl;
        exit(EXIT_SUCCESS);
    }

    // settings http server settings
    mg_set_protocol_http_websocket(mc); // setting http protocol

    server_opts.document_root = "."; // setting up the documents files
    
    server_opts.enable_directory_listing = "yes"; //  now it will list the server

    std::cout << "Server Running ctrl+c to stop" << std::endl;
    while (!stop)
    {
        
        mg_mgr_poll(&mgr, 1000);
        std::cout << mc->sa.sin.sin_zero;
        // printf("%s", server_opts.index_files);
        if(false)
            break;
    }   

    // Free Up all the memory if the server shuts down
    mg_mgr_free(&mgr);
}


int main (int args,std::string port) 
{
    // This is to dtermine if the user send the port number during execution or not
    if ( ConvertDataType::StringToInt(port) < 1 ) 
        server::fetchPort(port);
    std::cout << "Our server Created in port : " << "http://127.0.0.1:" << port << "/" << std::endl;

    //std::async(std::launch::async, server::initServer, port);
    server::initServer(port);

    std::cin.get();

    stop = true;

    return EXIT_SUCCESS;
}

