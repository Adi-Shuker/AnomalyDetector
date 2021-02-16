
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "Server.h"

Server::Server(int port)throw (const char*) {
    isRunning= true;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "socket failed";
    server.sin_family=AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(fd,(struct sockaddr*)&server,sizeof(server))<0)
        throw "bind failed";
    if(listen(fd,3)<0)
        throw "listen failed";

}
void Server::start(ClientHandler& ch)throw(const char*){
        t = new thread([&ch, this] {
            while(this->isRunning) {
                //cout << "waiting for a client" << endl;
                socklen_t clientSize = sizeof(this->client);
                //t1=new thread([&ch,&clientSize,this]{
                int aClient = accept(this->fd, (struct sockaddr *) &(this->client), &clientSize);
                if (aClient < 0)
                    throw "accept failure";
                //cout << "client connect!" << endl;

                ch.handle(aClient);//handle the client
                close(aClient);
                //});
            }
        });
}

void Server::stop(){
    isRunning=false;
    close(this->fd);
    t->join(); // do not delete this!
}

Server::~Server() {
}

