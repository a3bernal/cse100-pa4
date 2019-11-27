
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
int main(int argc, char* argv[]) {
    /*
    argv[0] = executable
    argv[1] = imdb file
    argv[2] = unweighted/weighted
    argv[3] = pairs
    argv[4] = write to
    */
    ActorGraph myGraph;
    // build the hashmaps
    myGraph.loadFromFile(argv[1], false);
    // build the edges
    myGraph.buildEdges(argv[1], false);
    // vector to pass in as pair
    vector<pair<string, string>> vectorPairs;
    // read the pairs and put them in a vector
    myGraph.pairsToVector(argv[3], vectorPairs);
    // file to write the path to
    ofstream out;
    out.open(argv[4]);
    // print the header
    out << "(actor)--[movie#@year]-->(actor)--..." << endl;
    for (int i = 0; i < vectorPairs.size(); i++) {
        string startAct = vectorPairs[i].first;
        ActorNode* startActor = myGraph.actorsMap.at(startAct);
        string endActor = vectorPairs[i].second;
        myGraph.BFSActors(startActor, endActor, out);
    }
    out.close();
    return 0;
}
