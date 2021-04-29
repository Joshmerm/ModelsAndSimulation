// A C++ program for Prim's Minimum 
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
// #include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
using namespace std;

#define Time 100

int aco(vector<vector<int> > tsp){
    vector<vector<vector<double>>> pTime = {};
    vector<vector<double> > pheromone = {};
    for(int i = 0; i < tsp.size(); i++){
        pheromone.push_back({0,0,0,0});
    }

    srand((unsigned) time(nullptr));
    for(int t = 0; t < Time; t++){
        //initilize probablity based on pheromones
        vector<int> probability = {};

        for(int i = 1; i < tsp.size(); i++)
            for(int j = 0; j < 33; j++)
                probability.push_back(i);
        
        vector<int> path = {};
        int pathlength = 0;


        for(int i = 0; i < tsp.size() - 1; i++){
            // set Probabilites based on pheromones using index
            for(int j = 1; j < pheromone[i].size(); j++){
                int prob = (int) (100 * pheromone[i][j]);
                for(int k = 0; k < prob; k++)
                    probability.push_back(j);
            }

            int result = (rand() % probability.size());

            // we look for a random city that hasn't already been chosen
            while((find(path.begin(), path.end(), probability[result])!=path.end()))
                result = (rand() % probability.size());

            // save the results
            path.push_back(probability[result]);
        }

        // print out of path its taking
        int ic = 0;
        cout << endl;
        for(int i = 0; i < path.size(); i++){
            cout << ic + 1 << "->" << path[i] + 1 << endl;
            ic = path[i];
        }
        cout << path[path.size() - 1] + 1 << "->" << 1 << endl;

        // update the pheromones with unit based 1 everytime it makes a full trip
        int initialcity = 0;
        for(int i = 0; i < path.size(); i++){
            pathlength += tsp[initialcity][path[i]];
            initialcity = path[i];
        }
        pathlength += tsp[initialcity][0];
        initialcity = 0;
        double pheromonePerUnit =  static_cast<double>(1) / (double)(1.0 * pathlength);

        // initilize pAnt (phereomones just from this path) 
        vector<vector<double>> pAnt = {};
        for(int i = 0; i < tsp.size(); i++){
            pAnt.push_back({0,0,0,0});
        }

        // update phereomones and pAnt from this ant
        for(int i = 0; i < path.size(); i++){
            pheromonePerUnit =  static_cast<double>(1) / (double)(1.0 * pathlength);
            pheromone[initialcity][path[i]] += pheromonePerUnit;
            pAnt[initialcity][path[i]] += pheromonePerUnit;
            initialcity = path[i];
        }
        pheromonePerUnit =  static_cast<double>(1) / (double)(1.0 * pathlength);
        pheromone[initialcity][0] += pheromonePerUnit;
        pAnt[initialcity][0] += pheromonePerUnit;

        // save a record of this ants pheromones
        pTime.push_back(pAnt);

        // if time has gone on for long enough we:
        if(t > 10){
            //delete the oldest pheromone in our records from pheromones used for probability &
            vector<vector<double>> temp = pTime[0];
            for(int i = 0; i < tsp.size(); i++)
                for(int j = 0; j < tsp.size(); j++)
                    pheromone[i][j] -= temp[i][j];

            // delete temp from records
            pTime.erase(find(pTime.begin(),pTime.end(),temp));
        }

        // Output for current pheromone state
        for(int i = 0; i < pheromone.size(); i++){
            cout << endl;
            for(int j = 0; j < pheromone[i].size(); j++){
                cout << pheromone[i][j] << ", ";
            }
        }
    }


    // We then find the most optimized route
    int loops = 0;
    int parent = 0;
    int totalLength = 0;
    vector<int> finalPath = {};
    cout << endl;
    while(loops < pheromone.size()){
        double last = 0;
        int index = 0;
        for(int j = 1; j < pheromone.size(); j++){
            
            if (last < pheromone[parent][j] && !(find(finalPath.begin(), finalPath.end(), j)!=finalPath.end())){
                last = pheromone[parent][j];
                index = j;
            }
        }
        finalPath.push_back(index);
        totalLength += tsp[parent][index];
        cout << parent + 1 << "->" << index + 1 << endl;
        parent = index;
        loops++;
    }

    cout << "Total Length: " << totalLength << endl;
    return totalLength;
}

// Driver code
int main() 
{ 
                        
    vector<vector<int> > tsp = { { -1, 10, 15, 20 },
                                 { 10, -1, 35, 25 },
                                 { 15, 35, -1, 30 },
                                 { 20, 25, 30, -1 } };
    int averagePath = 0;
    for(int i = 0; i < 10; i++)
        averagePath += aco(tsp);

    cout << "Average Path Found: " << averagePath / 10 << endl;
  
    return 0; 
} 