cmake_minimum_required(VERSION 3.16)

project(AnomalyDetector)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -std=c++11")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(AnomalyDetector anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h MainTrain.cpp SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h HybridAnomalyDetector.cpp HybridAnomalyDetector.h minCircle.cpp minCircle.h CLI.cpp CLI.h commands.h Server.cpp Server.h)