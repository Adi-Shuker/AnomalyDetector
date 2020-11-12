cmake_minimum_required(VERSION 3.16)
project(AnomalyDetector)

set(CMAKE_CXX_STANDARD 11)

add_executable(AnomalyDetector anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h MainTrain.cpp SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h)