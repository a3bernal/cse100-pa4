/* Author: Andres Bernal
 *
 * File Header: This file finds the shortest path from an actor
 * to another actor by running the BFS algorith on unweighted edges or
 * the dikjstras algorith on weight edges.
 *
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
/* This is the main method which computes the shortest distance from a actor
 * to another actor both on weighted and unweighted edges
 */
int main(int argc, char* argv[]) {
    /*
    argv[0] = executable
    argv[1] = imdb file
    argv[2] = unweighted/weighted
    argv[3] = pairs
    argv[4] = write to
    */
    const int actorsFile = 1;
    const int flag = 2;
    const int pairsFile = 3;
    const int writePath = 4;
    ActorGraph myGraph;
    // build the hashmaps
    myGraph.loadFromFile(argv[actorsFile], false);
    // build the edges
    myGraph.buildEdges(argv[actorsFile], false);
    // vector to pass in as pair
    vector<pair<string, string>> vectorPairs;
    // read the pairs and put them in a vector
    myGraph.pairsToVector(argv[pairsFile], vectorPairs);
    // file to write the path to
    ofstream out;
    out.open(argv[writePath]);
    string header = "(actor)--[movie#@year]-->(actor)--...";
    // print the header
    out << header << endl;
    // either runs the weighted or unweighted algorith
    bool weighted = false;
    if (*argv[flag] == 'w') {
        weighted = true;
    }

    for (int i = 0; i < vectorPairs.size(); i++) {
        string startAct = vectorPairs[i].first;
        ActorNode* startActor = myGraph.actorsMap.at(startAct);
        string endActor = vectorPairs[i].second;

        // unweighted algorithm
        if (weighted == false) {
            myGraph.BFSActors(startActor, endActor, out);
        }

        // weighted algorithm
        else {
            // returns a pair total distance , vector to reset variables
            pair<Edge*, vector<Edge*>> PAIR =
                myGraph.shortestPathWeighted(startActor, endActor);
            Edge* endingActor = PAIR.first;
            vector<Edge*> resetEdges = PAIR.second;
            myGraph.printPath(startActor, endingActor, out);
            // reset the variables
            myGraph.resetActorVariables();
        }
    }
    out.close();
    return 0;
}
