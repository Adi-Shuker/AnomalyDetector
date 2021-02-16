/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_


#include <thread>
#include <pthread.h>
#include <strings.h>
#include <cstring>
#include "CLI.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        //cout<<"in handle"<<endl;
        DefaultIO* socketIo= new SocketIO(clientID);
        CLI cli = CLI(socketIo);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in
    thread* t1;
    bool isRunning;
    int fd; //file descriptor the id of the client we currently connect with,
    sockaddr_in server;
    sockaddr_in client;

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void helperStart(ClientHandler& ch)throw(const char*);
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
