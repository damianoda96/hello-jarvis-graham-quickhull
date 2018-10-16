// C++ program to implement Quick Hull algorithm
// to find convex hull.

//Credit goes to the following for the algorithms used within this project
//Quickhull - https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/

#include "Point.h"
#include <set>
#include <vector>
#include <utility>

using namespace std;


// iPair is integer pairs
#define iPair pair<int, int>

// Stores the result (points of convex hull)
set<iPair> hull;

std::vector<iPair> convert_to_pair(std::vector<Point>);

// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(iPair p1, iPair p2, iPair p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
    (p2.second - p1.second) * (p.first - p1.first);
    
    if (val > 0)
    return 1;
    if (val < 0)
    return -1;
    return 0;
}

// Returns the square of distance between
// p1 and p2.
int dist(iPair p, iPair q)
{
    return (p.second - q.second) * (p.second - q.second) +
    (p.first - q.first) * (p.first - q.first);
}

// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDist(iPair p1, iPair p2, iPair p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
                (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(std::vector<iPair> a, int n, iPair p1, iPair p2, int side)
{
    int ind = -1;
    int max_dist = 0;
    
    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }
    
    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }
    
    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void q_printHull(std::vector<Point> points, int n, std::string outputFile)
{

    std::vector<iPair> a = convert_to_pair(points);
    // a[i].second -> y-coordinate of the ith point
    if (n < 3)
    {
        cout << "Convex hull not possible\n";
        return;
    }
    
    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (a[i].first < a[min_x].first)
        min_x = i;
        if (a[i].first > a[max_x].first)
        max_x = i;
    }
    
    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], 1);
    
    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], -1);
    
    std::ofstream myfile;
    
    myfile.open(outputFile);
    
    while (!hull.empty())
    {
        myfile << "(" <<( *hull.begin()).first << ", "
        << (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
        myfile << "\n";
    }
    
    myfile.close();
}

std::vector<iPair> convert_to_pair(std::vector<Point> points)
{
    std::vector<iPair> a;
    
    for(int i = 0; i < points.size(); i++)
    {
        iPair b = std::make_pair(points[i].x, points[i].y);
        a.push_back(b);
    }
    
    return a;
    
}

