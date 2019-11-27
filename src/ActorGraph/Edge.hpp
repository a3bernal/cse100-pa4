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
    //
    int priority;
    /* Constructor of Edge object */
    Edge(ActorNode* actor, MovieNode* movie) : actor(actor), movie(movie) {
        priority = 0;
    }
};
struct EdgePtrComp {
    /* Used for the priority queue to prioritize*/

    bool operator()(Edge* lhs, Edge* rhs) const {
        if (lhs->priority != rhs->priority) {
		// descending order
            return lhs->priority < rhs->priority;
        }
	// ascending order
        return lhs->actor > rhs->actor;
    }
};
#endif
