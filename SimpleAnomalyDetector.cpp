
#include "SimpleAnomalyDetector.h"
//default constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    threshold = 0.9;
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

//get 2 features and return their threshold that is the biggest dist between legal point to the
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
void SimpleAnomalyDetector::learnHelper(const TimeSeries& ts,float maxCorrelation,string f1, string f2, Point** points){
    if (maxCorrelation >= this->threshold) {
        correlatedFeatures newCf =  correlatedFeatures();
        newCf.corrlation = maxCorrelation;
        newCf.feature1 = f1;
        newCf.feature2 = f2;
        int size = ts.getColumn(f2).size();
        newCf.lin_reg = linear_reg(points, size);
        newCf.threshold = findThreshold(points, size, newCf.lin_reg) * 1.1;
        cf.push_back(newCf);
    }
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
        int size = ts.getColumn(featureName).size();
        Point **points = toPoints(ts.getColumn(ts.getFeaturesNames().at(i)), ts.getColumn(featureName), size);
        learnHelper(ts, maxCorrelation, ts.getFeaturesNames().at(i), featureName, points);
        //free points
        for(int i=0;i<size;i++){
            delete points[i];
        }
        delete points;
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    this->anomalyReportVector = vector<AnomalyReport>();
    for(int i = 1;i<=ts.getNumOfLine();i++){
        vector<pair<string, float>> vec = ts.getLine(i);
        for(int j=0;j<cf.size();j++){
            Point p = Point(ts.getValue( vec, cf.at(j).feature1), ts.getValue( vec, cf.at(j).feature2));
            if(cf.at(j).corrlation>=this->threshold) {
                if (dev(p, cf.at(j).lin_reg) > cf.at(j).threshold) {
                    AnomalyReport anomalyReport = AnomalyReport(cf.at(j).feature1 + "-" + cf.at(j).feature2, i);
                    anomalyReportVector.push_back(anomalyReport);
                }
            }else{
                if (dev(p, Point(cf.at(j).center->x,cf.at(j).center->y)) > cf.at(j).threshold) {
                    AnomalyReport anomalyReport = AnomalyReport(cf.at(j).feature1 + "-" + cf.at(j).feature2, i);
                    anomalyReportVector.push_back(anomalyReport);
                }
            }
        }
    }
    return  anomalyReportVector;
}