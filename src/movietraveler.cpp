/* Author: Andres Bernal
 *
 * File Header: This file takes in two arguments , the first argument is a file
 * with a list of actors and movies they have been in. The second argument is
 * a file to write MST which means that it finds the shortest path to visit all
 * the actors from the first file passed in.
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"
/* This is the main method method that writes a MST to the second argument*/
int main(int argc, char* argv[]) {
    /*
    argv[0] = executable
    argv[1] = imdb file
    argv[2] = write Minimum spanning tree
    */
    const int actorsFile = 1;
    const int writeMST = 2;
    ActorGraph myGraph;
    // build the hashmaps
    myGraph.loadFromFile(argv[actorsFile], false);
    // build the edges
    myGraph.buildEdges(argv[actorsFile], true);
    // loop through the priority queue that holds all the edges
    int numConnectedEdges = 0;
    // vector to print the path
    int totalWeight = 0;
    // Maxinum # of edges is #Actors - 1
    int maxEdges = myGraph.actorsMap.size();
    // the file to write the path and number of total Weight
    ofstream out;
    out.open(argv[writeMST]);

    // used for writing to file
    string leftA = "<--";
    string rightA = "-->";
    string leftP = "(";
    string rightP = ")";
    string midMovie = "#@";
    string leftB = "[";
    string rightB = "]";
    string header = "(actor)<--[movie#@year]-->(actor)";
    out << header << endl;

    while (myGraph.pq.empty() == false) {
        // break once a MST has been built
        if (numConnectedEdges >= maxEdges - 1) {
            break;
        }

        ActorNode* startActor = myGraph.pq.top().first;
        Edge* endingEdge = myGraph.pq.top().second;
        ActorNode* endingEdgeActor = endingEdge->actor;
        MovieNode* currMovie = endingEdge->movie;
        // true if the actor vertex got unioned false otherwise
        bool unioned = myGraph.unionActors(startActor, endingEdgeActor);
        if (unioned == true) {
            // to know when to stop looping
            numConnectedEdges++;
            totalWeight = totalWeight + endingEdge->weight;
            string path = leftP + startActor->name + rightP + leftA + leftB +
                          currMovie->title + midMovie +
                          to_string(currMovie->year) + rightB + rightA + leftP +
                          endingEdgeActor->name + rightP;
            // print the path unioned
            out << path << endl;
        }
        myGraph.pq.pop();
    }
    // write the information of MST
    out << "#NODE CONNECTED: " + to_string(maxEdges) << endl;
    out << "#EDGE CHOSEN: " + to_string(maxEdges - 1) << endl;
    out << "TOTAL EDGE WEIGHTS: " + to_string(totalWeight) << endl;
    out.close();
    // reset the variables
    while (myGraph.pq.empty() == false) {
        myGraph.pq.pop();
    }
    myGraph.resetActorVariables();
    return 0;
}
