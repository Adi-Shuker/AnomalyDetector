

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;  //the longest distance between the line and the point in case of bigger than 0.5 is the radius*1.1
    Point* center;  //the center of the circle(in case > 0.5)
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    vector<correlatedFeatures> cf;
    float threshold;    //The threshold from which the feature are considered correlatives
    vector<AnomalyReport> anomalyReportVector;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }
    void setCorrelationThreshold(float threshold){
        this->threshold=threshold;
    }
    float getThreshold(){
        return threshold;
    }
    vector<AnomalyReport> getAnomalyReportVector(){
        return this->anomalyReportVector;
    }
protected:
    virtual void learnHelper(const TimeSeries& ts,float maxCorrelation,string f1, string f2, Point** points);

    virtual Point **toPoints(vector<float> feature1, vector<float> feature2, int size);

    virtual float findThreshold(Point **points, int size, Line l);

};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
