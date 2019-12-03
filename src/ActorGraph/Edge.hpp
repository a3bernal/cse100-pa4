/**
 * File Header: This file holds the Edge object which conects two actors
 * by a common movie that they both appeared in. The edge consist of a
 * Actor node and and a Movie node.
 *
 * Author: Andres Bernal
 * Sources of Help: N/A
 */
#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <limits>
#include <string>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"
using namespace std;

// class ActorNode;

class Edge {
  public:
    // the actor that that connects the edge with calling actor
    ActorNode* actor;
    // the movie that connects both actors
    MovieNode* movie;
    // previous edge used for BFS
    Edge* previous;
    // used for pq
    int distance;
    int weight;
    // used for pq
    int priority;
    /* Constructor of Edge object */
    Edge(ActorNode* actor, MovieNode* movie) : actor(actor), movie(movie) {
        priority = 0;
        distance = numeric_limits<int>::max();
        weight = 0;
    }
};
struct EdgePtrComp {
    /* Used for the priority queue to prioritize*/
    bool operator()(Edge* lhs, Edge* rhs) const {
        return lhs->distance > rhs->distance;
    }
};
#endif
