/*
 * animaly_detection_util.cpp
 *
 * Author: 209298587 Adi Elgali
 */

#include <math.h>
#include <bits/streambuf_iterator.h>
#include <algorithm>
#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;

float avg(float* x, int size){
    float sum=0.0;
    for(int i=0;i<size;i++){
        sum = sum+x[i];
    }
    return (sum/(float)size);
}

// returns the variance of X and Y
float var(float* x, int size){
    float sum=0.0;
    float sum_squares =0.0;
    for(int i=0;i<size;i++){
        float num=*(x+i);
        sum += num;
        sum_squares += num*num;
    }
    float mu=(1.0/size)*sum;
    return ((1.0/size)*sum_squares-(mu*mu));
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float * result = new float[size];
    for(int i=0;i<size;i++) {
        result[i] = x[i] * y[i];
    }
    float ans = avg(result,size)-avg(x,size)*avg(y,size);
    delete[] result;
    return ans;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    return (cov(x,y,size)/(sqrt(var(x,size))*sqrt(var(y,size))));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
    float* x= new float[size];
    float* y= new float[size];
    for(int i=0;i<size;i++){
        x[i]=(*(points+i))->x;
        y[i]=(*(points+i))->y;
    }
    float a = cov(x,y,size)/var(x,size);
    float x_1 = avg(x,size);
    float y_1 = avg(y,size);
    float b = y_1-a*x_1;
    delete[] x;
    delete[] y;
    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    return dev(p,linear_reg(points,size));
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    return abs(l.f(p.x)-p.y);
}

// returns the deviation between point p and the line
float dev(Point p1,Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}






