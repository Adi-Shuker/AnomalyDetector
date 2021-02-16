

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include <sys/socket.h>
#include "commands.h"
#include "unistd.h"

using namespace std;

class SocketIO: public DefaultIO{
    int clientID;
public:
    SocketIO(int clientID){
       this->clientID=clientID;
    }
    virtual string read(){
        string clientInput="";
        char c=0;
        ::read(clientID,&c,sizeof(char));
        while(c!='\n'){
            clientInput+=c;
            ::read(clientID,&c,sizeof(char));
        }
        return clientInput;
    }
    virtual void write(string text){
       int i=0;
        while(i<text.size()){
            ::send(clientID,&text[i],1,0);
            i++;
        }
    }

    virtual void write(float f){
        ::send(clientID,&f,sizeof(f),0);
    }

    virtual void read(float* f){
        char buffer[1024];
        bzero(buffer, 1024);
        ::read(clientID,buffer,100);
        *f=stof(buffer);
    }

    void close(){

    }
    ~SocketIO(){
        close();
    }
};

class CLI {
    DefaultIO* dio;
    vector<Command*> Commands;
    TimeSeries* train;
    TimeSeries* test;
    HybridAnomalyDetector* ad;
    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
    HybridAnomalyDetector* getHybridAnomalyDetector(){
        return this->ad;
    }
};

#endif /* CLI_H_ */
