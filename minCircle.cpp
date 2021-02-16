#include "minCircle.h"
// 33791218 20929858
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function that returns the dist between two points
float dist(Point p1,Point p2)
{
    return sqrt(pow((p1.x- p2.x), 2) + pow((p1.y - p2.y), 2));
}

// function that get circle and point and check if the point is in the circle
bool pointInCircle(const Circle& c,const Point& p){
    return dist(c.center, p) <= c.radius;
}

// check if all the point are in the circle
bool isAllPointInCircle(const Circle& c, const vector<Point>& points, size_t size){
    for(int i=0; i<size; i++){
        if(!pointInCircle(c, points[i])){
            return false;
        }
    }
    return true;
}

// Function that returns the smallest circle that intersects 2 points
Circle from2Points(Point p1, Point p2)
{
    // Set the center to be the midpoint of p1 and p2
    Point center = Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
    // Set the radius to be half the dist p1p2
    // Set the circle with the center point and the radius
    return Circle(center, dist(p1, p2) / 2.0);

}

// Function that returns the circle that intersects 3 points
Circle from3Points(Point p1, Point p2, Point p3)
{
    float a = pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2);
    float b = pow(p3.x - p1.x,2) + pow(p3.y - p1.y,2);
    float c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    float x = ((p3.y - p1.y) * a - (p2.y - p1.y) * b) / (2 * c);
    float y = ((p2.x - p1.x) * b - (p3.x - p1.x) * a) / (2 * c);
    Point I = Point(x,y);
    I.x += p1.x;
    I.y += p1.y;
    return Circle(I, dist(I, p1));
}

//only if size of vec smallest or equal than 3
Circle baseCase(vector<Point>& vec){
int size = vec.size();

    if(size==0){
        return(Circle(Point(0,0),0));
    }
    else if(size==1){
        return(Circle(vec[0],0));
    }
    else if(size==2){
        return from2Points(vec[0], vec[1]);
    }

    //check if exist couple of points that enclose circle
    for(int i=0; i<3; i++){
        for(int j=i+1; j<3; j++){
            Circle circle = from2Points(vec[i], vec[j]);
            if(isAllPointInCircle(circle,vec,size)){
                return circle;
            }
        }
    }
    return from3Points(vec[0], vec[1], vec[2]);
}

Circle welzl(vector<Point>& points, int size, vector<Point> vec){
    //base case
    if(size ==0 || vec.size()==3){
        return baseCase(vec);
    }

    // Choose a point from the vector points randomly
    int i = rand() %size;
    Point pointToRemove = points[i];

    // Put this point at the end of the vecteur points because it's
    // more efficient than deleting from the middle of the vector
    swap(points[i], points[size - 1]);

    // get the minCircle from the vector of points
    Circle newCircle = welzl(points, size-1, vec);

    // If the circle contains pointToRemove, return the circle
    if(pointInCircle(newCircle, pointToRemove)){
        return newCircle;
    }
    // Otherwise, must be on the boundary of the minCircle
    vec.push_back(pointToRemove);

    // Return the minCircle for vecteurPoints - {pointToRemove} and vec U {pointToRemove}
    return welzl(points,size-1,vec);
}

// function that returns the minCircle
Circle findMinCircle(Point** points,size_t size){
    vector<Point> vec;
    vector<Point> pointsCopy;
    for( int i=0;i<size;i++){
        pointsCopy.push_back(Point(points[i]->x, points[i]->y));
    }
    Circle circle =welzl(pointsCopy,size,vec);
    return circle;
}
