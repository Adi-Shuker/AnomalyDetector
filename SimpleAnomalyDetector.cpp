
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}

Point **SimpleAnomalyDetector::toPoints(vector<float> feature1, vector<float> feature2, int size) {
    Point **points = new Point *[size];
    for (int i = 0; i < size; i++) {
        points[i] = new Point(feature1.at(i), feature2.at(i));
    }
    return points;
}

//get 2 features and return their threshold that is the biggest distance between legal point to the
//regression line they created.
float SimpleAnomalyDetector::findThreshold(Point **points, int size, Line l) {
    float maxDistance = 0;
    float currentDistance = 0;
    for (int i = 0; i < size; i++) {
        currentDistance = dev(*points[i], l);
        if (maxDistance < currentDistance) {
            maxDistance = currentDistance;
        }
    }
    return maxDistance;
}

//implement the preliminary stage-take file of proper flight
//and check for every feature who is the most correlative to him
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    float maxCorrelation = -1;
    string featureName;
    for (int i = 0; i < ts.getFeaturesNames().size(); i++) {
        maxCorrelation = -1;
        featureName = "";
        for (int j = i + 1; j < ts.getFeaturesNames().size(); j++) {
            float currentCorrelation = abs(pearson(ts.getColumn(ts.getFeaturesNames().at(i)).data(),
                                                   ts.getColumn(ts.getFeaturesNames().at(j).data()).data(),
                                                   ts.getNumOfLine() - 1));
            if (maxCorrelation < currentCorrelation) {
                maxCorrelation = currentCorrelation;
                featureName = ts.getFeaturesNames().at(j);
            }
        }
        //check if the element is already exist in the vector
        int isExist = 0;
        for (int k = 0; k < cf.size(); k++) {
            if (cf.at(k).feature1 == featureName && cf.at(k).feature2 == ts.getFeaturesNames().at(i)) {
                isExist = 1;
            }
        }
        if (!(isExist) && maxCorrelation >= 0.9) {
            correlatedFeatures newCf =  correlatedFeatures();
            newCf.corrlation = maxCorrelation;
            //make sure that feature1 is the left column between them
            if (i<ts.getPlace(ts.getFeaturesNames(),featureName)) {
                newCf.feature1 = ts.getFeaturesNames().at(i);
                newCf.feature2 = featureName;
            }else{
                newCf.feature1 = featureName;
                newCf.feature2 = ts.getFeaturesNames().at(i);
            }
            int size = ts.getColumn(newCf.feature2).size();
            Point **points = toPoints(ts.getColumn(newCf.feature1), ts.getColumn(newCf.feature2), size);
            newCf.lin_reg = linear_reg(points, size);
            newCf.threshold = findThreshold(points, size, newCf.lin_reg) * 1.1;
            //free points
            for(int i=0;i<size;i++){
                delete points[i];
            }
            delete points;
            cf.push_back(newCf);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> anomalyReportVector = vector<AnomalyReport>();
    for(int i = 1;i<=ts.getNumOfLine();i++){
        vector<pair<string, float>> vec = ts.getLine(i);
        for(int j=0;j<cf.size();j++){
            float x = ts.getValue( vec, cf.at(j).feature1);
            float y = ts.getValue( vec, cf.at(j).feature2);
            Point p = Point(x, y);
            if(dev( p,cf.at(j).lin_reg)>cf.at(j).threshold){
                AnomalyReport anomalyReport = AnomalyReport(cf.at(j).feature1 + "-" + cf.at(j).feature2, i);
                anomalyReportVector.push_back(anomalyReport);
            }
        }
    }
    return  anomalyReportVector;
}