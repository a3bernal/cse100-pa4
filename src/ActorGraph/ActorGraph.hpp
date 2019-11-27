/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"

// Maybe include some data structures here

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  public:
    // hashmap to store the actor names as keys and actorNode as values
    unordered_map<string, ActorNode*> actorsMap;
    // hashmap to store the movies
    unordered_map<string, MovieNode*> moviesMap;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    bool buildEdges(const char* in_filename, bool use_weighted_edges);

    bool pairsToVector(const char* in_filename,
                       vector<pair<string, string>>& actorPairs);

    bool actorsToVector(const char* in_filename, vector<string> &singleActors);

    int BFSActors(ActorNode* startingActor, string endingActor, ofstream& out);

    void resetActorVariables();

    void printPath(ActorNode* start, Edge* end, ofstream& out);

    void linkCollabs(ActorNode* start, ofstream& outCollab,
                              ofstream& outUncollab);
};

#endif  // ACTORGRAPH_HPP
