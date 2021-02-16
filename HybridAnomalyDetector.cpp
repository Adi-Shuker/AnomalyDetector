
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries &ts){
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
        if(maxCorrelation>=this->threshold) {
            learnHelper(ts, maxCorrelation, ts.getFeaturesNames().at(i), featureName, points);
        }else if(maxCorrelation>0.5){
            correlatedFeatures newCf =  correlatedFeatures();
            newCf.corrlation = maxCorrelation;
            newCf.feature1 = ts.getFeaturesNames().at(i);
            newCf.feature2 = featureName;
            Circle circle =findMinCircle(points,size);
            newCf.threshold = circle.radius * 1.1;
            newCf.center = new Point(circle.center.x,circle.center.y);
            cf.push_back(newCf);
        }
        //free points
        for(int i=0;i<size;i++){
            delete points[i];
        }
        delete points;
    }
}

