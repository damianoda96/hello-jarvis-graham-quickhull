//Deven Damiano - dad152@zips.uakron.edu
//
//Credit goes to the following for the algorithms used within this project
//Graham Scan - https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
//Javis March - https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
//Quickhull - https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "Point.h" //simple Point struct to create coordinate pairs
#include "quickhull.hpp"
#include "graham.hpp"
#include "jarvis.hpp"
#include <vector>
#include <chrono>

//TODO: FIND WAY TO MEASURE RUNTIME OF FUNCTIONS FOR ADDITIONAL WORKSHEET

std::vector<Point> store_points(std::string);
int str_to_int(std::string);
Point * vect_to_array(std::vector<Point>);

int main(int argc, char *argv[])
{
    //Second project starts here
    if (argc < 3)
    {
        std::cout << "wrong format! should be \"a.exe algType dataFile\"";
    }
    else
    {
        std::string algType = argv[1];
        std::string dataFilename = argv[2];
        std::string outputFile = "";
        //read your data points from dataFile (see class example for the format)
        
        //grab points array..
        std::vector<Point> points = store_points(dataFilename);
        
        if (algType == "G") {
            //call your Graham Scan algorithm to solve the problem
            
            outputFile = "hull_G.txt";
            
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        
            g_convexHull(points, points.size(), outputFile);
            
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            
            int duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            
            std::cout << duration << std::endl;
        }
        else if (algType == "J") {
            //call your Javis March algorithm to solve the problem
            outputFile = "hull_J.txt";
            
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            
            j_convexHull(points, points.size(), outputFile);
            
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            
            int duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            
            std::cout << duration << std::endl;
        }
        else { //default
            //call your Quickhull algorithm to solve the problem
            outputFile = "hull_Q.txt";
            
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            
            q_printHull(points, points.size(), outputFile);
            
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            
            int duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            
            std::cout << duration << std::endl;
        }
        
        //write your convex hull to the outputFile (see class example for the format)
        //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
    }
        
        return 0;
}
    
std::vector<Point> store_points(std::string dataFilename)
{
    std::vector<Point> points;
    std::string coords [2];
    
    std::ifstream myfile;
    myfile.open(dataFilename);
    
    std::string str;
    std::vector<std::string> str_v;
    
    while (std::getline(myfile, str))
    {
        //std::cout << str << std::endl;
        
        str_v.push_back(str);
    }
    
    myfile.close();
    
    //Now, create pair vector

    for(int i = 0; i < str_v.size(); i++)
    {
        std::string str1 = str_v[i];
        std::string strX = "";
        std::string strY = "";
        
        bool hit_tab = false;
        
        for(int j = 0; j < str1.length(); j++)
        {
            
            if(str1[j] == '\t')
            {
                hit_tab = true;
                //std::cout << "found" << std::endl;
                //figure out a method for creating pairs with str_to_int
            }
            else if(!hit_tab) //x
            {
                strX += str1[j];
            }
            else //y
            {
                strY += str1[j];
            }
        }
        
        points.push_back(Point(str_to_int(strX),str_to_int(strY)));
        //points[i].x = str_to_int(strX);
        //points[i].y = str_to_int(strY);
        
        //points[i].print();
    }
    
    return points;
}

//small function to convert strings to integers

int str_to_int(std::string str)
{
    std::stringstream ss(str);
    
    // The object has the value 12345 and stream
    // it to the integer x
    int x = 0;
    ss >> x;
    
    return x;
}
