/*
 * Author: Andres Bernal
 *
 * File Header: This file reads in four arguments and the first argument is a
 * file with a list of actors and movies they have been in the second file it
 * takes in is a list of actors to predict their future collaborations with
 * other actors. The third and foruth arguments it takes in is a file to write
 * the actors future collaboration and future collaboration with another actor
 * it has not worked with
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
/* This method takes in four arguments and prints the predicted future
 * collaborations between actors
 */
int main(int argc, char* argv[]) {
    /*
    argv[0] = executable
    argv[1] = imdb file
    argv[2] = single actor file
    argv[3] = write to file collab
    argv[4] = write to file uncollab
    */

    const int FIRST_ARG = 1;
    const int SEC_ARG = 2;
    const int THIRD_ARG = 3;
    const int FOURTH_ARG = 4;
    ActorGraph myGraph;
    char* actorsFile = argv[FIRST_ARG];
    char* actorFile = argv[SEC_ARG];
    char* writeCollab = argv[THIRD_ARG];
    char* writeUncollab = argv[FOURTH_ARG];
    // build the hashmaps
    myGraph.loadFromFile(actorsFile, false);
    // build the edges
    myGraph.buildEdges(actorsFile, false);
    // vector to pass in a sinle line actor
    vector<string> actorsList;
    // read the pairs and put them in a vector
    myGraph.actorsToVector(actorFile, actorsList);

    // file to write Collab predictions
    ofstream outCollab;
    outCollab.open(writeCollab);

    // file to write Uncollab to
    ofstream outUncollab;
    outUncollab.open(writeUncollab);
    // print the header
    outCollab << "Actor1,Actor2,Actor3,Actor4" << endl;
    outUncollab << "Actor1,Actor2,Actor3,Actor4" << endl;
    // Computes the future links between actors
    for (int i = 0; i < actorsList.size(); i++) {
        string startAct = actorsList[i];
        ActorNode* startActor = myGraph.actorsMap.at(startAct);
        myGraph.linkCollabs(startActor, outCollab, outUncollab);
        outCollab << endl;
        outUncollab << endl;
    }
    // close the writing files
    outCollab.close();
    outUncollab.close();
    return 0;
}
