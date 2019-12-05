/*
 * ActorGraph.hpp
 * Author: Andres Bernal
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
 * This class initializes the Actor Graph and its methods defined
 */
class ActorGraph {
  public:
    class CompareDist {
      public:
        bool operator()(pair<ActorNode*, Edge*> n1,
                        pair<ActorNode*, Edge*> n2) {
            return n1.second->weight > n2.second->weight;
        }
    };
    // hashmap to store the actor names as keys and actorNode as values
    unordered_map<string, ActorNode*> actorsMap;
    // hashmap to store the movies
    unordered_map<string, MovieNode*> moviesMap;
    // priority queue used for MST
    priority_queue<pair<ActorNode*, Edge*>, vector<pair<ActorNode*, Edge*>>,
                   CompareDist>
        pq;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

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

    /* This method builds the edges between the actors by a common movie. It
     * reads in a file and builds the connections -- given that both of the
     * hashmaps are filled by the previous  method (loadFromFile)
     */
    bool buildEdges(const char* in_filename, bool use_weighted_edges);

    /* This method reads a file in the format actor<tab>actor2 and adds them
     * into a vector as a pair until it finishes reading all the pairs
     */
    bool pairsToVector(const char* in_filename,
                       vector<pair<string, string>>& actorPairs);

    /*This method reads in a file puts the actors into a vector until the EOF */
    bool actorsToVector(const char* in_filename, vector<string>& singleActors);

    /* This method finds the shortest path from the starting actor to the
     * ending actor on a unweighted edge graph and print the path from the
     * start to the end to a file
     */
    int BFSActors(ActorNode* startingActor, string endingActor, ofstream& out);
    /* Resets the variables for the edges and actor nodes*/
    void resetActorVariables();

    /* This method prints the path from the starting vertex to ending vertex*/
    void printPath(ActorNode* start, Edge* end, ofstream& out);

    /* This method predicts the future collaborations between starting actor
     * and another actor, the first prediction with another one is with someone
     * the starting actor has worked with and the other prediction is with
     * someone the start actor has not collaborated in a movie with
     */
    void linkCollabs(ActorNode* start, ofstream& outCollab,
                     ofstream& outUncollab);

    /* This method find the shortest weighted path from a starting actor to
     * another actor based on the input and returns the total weighted path
     */
    pair<Edge*, vector<Edge*>> shortestPathWeighted(ActorNode* startActor,
                                                    string endActor);

    /* This method finds the root of the Actor Node passed in and retuns the
     * root which is defined as the sentinel
     */
    ActorNode* findSentinel(ActorNode* currActor);

    /* This method compresses the graph by pointing the curr vertex to the
     * sentinel node for a efficent findSentinel time
     */
    void pathCompression(vector<ActorNode*> path, ActorNode* sentinel);

    /* This method connects two edges by connection two Actors vertex together
     * and modifies their size. Returns true if it was succesful
     */
    bool unionActors(ActorNode* actor1, ActorNode* actor2);
};

#endif  // ACTORGRAPH_HPP
