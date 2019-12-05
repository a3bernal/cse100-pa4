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
#include <limits>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"
using namespace std;

/* ActorNode class that represents a vertex in the Graph */
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
    // used for movietraveler
    ActorNode* parent;
    // used for movietraveler to know which two verties is parent
    int size;

    /* Constructor to initialize a ActorNode */
    ActorNode(string name) : name(name) {
        connections = vector<Edge*>();
        visited = false;
        previous = nullptr;
        distance = numeric_limits<int>::max();
        priority = 0;
        added = false;
        parent = nullptr;
        size = 1;
    }
};
/* This struct is used as the comparison basis for a priority queue*/
struct ActorPtrComp {
    bool operator()(ActorNode* lhs, ActorNode* rhs) const {
        if (lhs->priority != rhs->priority) {
            return lhs->priority < rhs->priority;
        }
        return lhs->name > rhs->name;
    }
};
#endif
