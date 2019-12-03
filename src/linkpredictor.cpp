

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
    argv[2] = single actor file
    argv[3] = write to file collab
    argv[4] = write to file uncollab
    */
    ActorGraph myGraph;
    // build the hashmaps
    myGraph.loadFromFile(argv[1], false);
    // build the edges
    myGraph.buildEdges(argv[1], false);
    // vector to pass in a sinle line actor
    vector<string> actorsList;
    // read the pairs and put them in a vector
    myGraph.actorsToVector(argv[2], actorsList);

    // file to write Collab predictions
    ofstream outCollab;
    outCollab.open(argv[3]);

    // file to write Uncollab to
    ofstream outUncollab;
    outUncollab.open(argv[4]);
    // print the header
    outCollab << "Actor1,Actor2,Actor3,Actor4" << endl;
    outUncollab << "Actor1,Actor2,Actor3,Actor4" << endl;
    for (int i = 0; i < actorsList.size(); i++) {
        string startAct = actorsList[i];
        ActorNode* startActor = myGraph.actorsMap.at(startAct);
        myGraph.linkCollabs(startActor, outCollab, outUncollab);
        outCollab << endl;
        outUncollab << endl;
    }
    outCollab.close();
    outUncollab.close();
    return 0;
}
