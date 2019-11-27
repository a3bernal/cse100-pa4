/* File Header: This file is the representation Node of a Actor. These nodes are
 * used to show the relationship between different actor is the Actorgraph when
 * it gets bbuild
 *
 * Author: Andres Bernal
 * Sources of Help: N/A
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <iostream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"

using namespace std;
class ActorNode {
  public:
    // name of the actor
    string name;
    // a list of edges that this actor has with other actors
    vector<Edge*> connections;
    // check if it was visited during BFS search
    bool visited;
    // used for BFS traversing to find path
    Edge* previous;
    // used for BFS for distance to origin vertex
    int distance;
    // used for LinkPrediction Second Level
    int priority;
    // used for Link Prediction Second Level
    bool added;

    /* Constructor to initialize a ActorNode */
    ActorNode(string name) : name(name) {
        connections = vector<Edge*>();
        visited = false;
        previous = nullptr;
        distance = -1;
        priority = 0;
        added = false;
    }


/*bool operator <(ActorNode* actor1)const {
	cout << "here" << endl;
        if( this->name > actor1->name){
                return true;
        }
        return false;
}*/

};
struct ActorPtrComp {
    bool operator()(ActorNode* lhs, ActorNode* rhs) const {
        if (lhs->priority != rhs->priority) {
            return lhs->priority < rhs->priority;
        }
        return lhs->name > rhs->name;
    }
};
#endif
