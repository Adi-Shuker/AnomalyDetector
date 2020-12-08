

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class TimeSeries {
    //use map<string lineNumber, map<name of the feature, value in specific line>
    map<int, vector<pair<string, float>>> featuresMap;
    //vector of the feature name by their features names
    vector<string> featuresNames;
    int numOfLine;
public:

    TimeSeries(const char *CSVfileName);

    const vector<string> getFeaturesNames() const;
    const int getPlace(vector<string> featuresNames, string name) const;

    vector<pair<string, float>> getLine(int i) const;

    float getValue(vector<pair<string, float>> vec, string name)const;

    vector<float> getColumn(string featureName) const;

    const int getNumOfLine() const;


};


#endif /* TIMESERIES_H_ */
