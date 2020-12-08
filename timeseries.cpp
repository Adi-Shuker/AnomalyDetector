#include "timeseries.h"

//constructor
TimeSeries::TimeSeries(const char *CSVfileName) {
    ifstream myFileStream(CSVfileName);
    if (!myFileStream.is_open()) {
        cout << "File failed to open" << endl;
    }
    string line;
    string subString;
    //the first list is the features names
    getline(myFileStream, line);
    stringstream ss(line);
    //read the names of the features
    while (getline(ss, subString, ',')) {
        featuresNames.push_back(subString);
    }
    numOfLine = 0;
    //read their value
    while (getline(myFileStream, line)) {
        numOfLine++;
        stringstream ss(line);
        vector<pair<string, float>> vec;
        for (int i = 0; i < featuresNames.size(); i++) {
            getline(ss, subString, ',');
            vec.push_back({featuresNames[i], stof(subString)});
        }
        featuresMap[numOfLine]=vec;
//        featuresMap.insert({numOfLine, vec});
    }
    myFileStream.close();
};

const vector<string> TimeSeries::getFeaturesNames() const {
    return featuresNames;
};

//this function return the i-est line(from 1-(n-1)) not include the first line(features name)
vector<pair<string, float>> TimeSeries::getLine(int i) const {
    return featuresMap.at(i);
};
//return the key of the string in the vector
float TimeSeries::getValue(vector<pair<string, float>> vec, string name)const{
    for(int i=0;i<vec.size();i++){
        if(!vec.at(i).first.compare(name)){
            return vec.at(i).second;
        }
    }
}

//the function return the index of name in FeatureName vector and -1 if he not in the vector
const int TimeSeries::getPlace(vector<string> featuresNames, string name) const {
    int i = 0;
    for (vector<string>::iterator it = featuresNames.begin(); it != featuresNames.end(); ++it) {
        if (!it->compare(name)) {
            return i;
        }
        i += 1;
    }
}

vector<float> TimeSeries::getColumn(string featureName) const {
    vector<float> vec;
    for (map<int, vector<pair<string, float>>>::const_iterator it = featuresMap.begin();
         it != featuresMap.end(); it++) {
        for (int i = 0; i < featuresNames.size(); i++) {
            //they are equal
            if (!it->second.at(i).first.compare(featureName)) {
                vec.push_back(it->second.at(i).second);
            }
        }
    }
    return vec;
};

const int TimeSeries::getNumOfLine() const {
    return numOfLine;
}
