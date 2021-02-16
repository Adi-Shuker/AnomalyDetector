#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->train = nullptr;
    this->test = nullptr;
    this->ad = new HybridAnomalyDetector();
}

void CLI::start(){
    //add all the commands to the vector
    this->Commands.push_back(new uploadCommand(this->dio));
    this->Commands.push_back(new setCorrelationCommend(this->dio,this->ad));
    this->Commands.push_back(new detectAnomalies(this->dio,this->ad,(const TimeSeries**)&this->train,(const TimeSeries**)&this->test));
    this->Commands.push_back(new displayResultsCommend(this->dio, this->ad));
    this->Commands.push_back(new analyzeAlgorithmCommend(this->dio,this->ad,(const TimeSeries**)&this->test));
    this->Commands.push_back(new exitCommend(this->dio));
    //run the menu
    int exit=0;
    do{
        this->dio->write("Welcome to the Anomaly Detection Server.\n");
        this->dio->write("Please choose an option:\n");
        for(int i=0 ;i<this->Commands.size();i++) {
            this->dio->write( to_string(i+1)+"." + this->Commands.at(i)->getString());
        }
        int index = stoi(this->dio->read());
        this->Commands.at(index - 1)->execute();
        if(!this->Commands.at(index-1)->getString().compare("exit\n")){
            exit=1;
        }
    }while(!exit);
}

CLI::~CLI() {
}

