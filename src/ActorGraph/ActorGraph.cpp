/*
 * ActorGraph.cpp
 * Author: Andres Berna;
 *
 * File Header : This file is meant to exist as a container for starter code
 * that you can use to read the input file format defined in imdb_2019.tsv.
 * Feel free to modify any/all aspects as you wish. It contains all the methods
 * used for the executables
 */
#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

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
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        // used for lookup since movies may have same title w dofferent year
        string movie_title_year = movie_title + to_string(year);
        // if the actor is not in the hashmap then add it as a key
        // with a value of actors node
        if (actorsMap.find(actor) == actorsMap.end()) {
            ActorNode* actorNode = new ActorNode(actor);
            actorsMap.insert(make_pair(actor, actorNode));
        }

        // if its not in the hashmap add movie title string as key and movie
        // node as the value
        if (moviesMap.find(movie_title_year) == moviesMap.end()) {
            MovieNode* movieNode = new MovieNode(movie_title, year);
            // returns a actor to be added to the movie cast
            ActorNode* actorInMovie = actorsMap.at(actor);
            // add the actor to the MovieNode cast vector
            movieNode->cast.push_back(actorInMovie);
            moviesMap.insert(make_pair(movie_title_year, movieNode));

        }
        // if the movie is in the hashmap just add the actor to the movie cast
        else {
            MovieNode* currMovie = moviesMap.at(movie_title_year);
            // get the pointer to not create new objects of the same actor
            ActorNode* actorInMovie = actorsMap.at(actor);
            // add the actor to the cast
            currMovie->cast.push_back(actorInMovie);
        }

        // end of while loop
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* This method builds the edges between the actors by a common movie. It reads
 * in a file and builds the connections -- given that both of the hashmaps are
 * filled by the previous  method (loadFromFile)
 */
bool ActorGraph::buildEdges(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);
        // used for lookup since movies may have same title w different year
        string movie_title_year = movie_title + to_string(year);
        // The read in actor from the file -- assumes actor is in the hashmap
        ActorNode* currActor = actorsMap.at(actor);

        // The read in movie from the file -- assumes movies is in the hashmap
        MovieNode* currMovie = moviesMap.at(movie_title_year);
        // Loop through each actor in the current movie read in
        for (int i = 0; i < currMovie->cast.size(); i++) {
            // dont add its own actor as an edge
            if (currActor->name == currMovie->cast[i]->name) {
            } else {
                int currYear = 2019;
                // create a edge object to append it to the actors connections
                Edge* connection = new Edge(currMovie->cast[i], currMovie);
                int edgeWeight = 1 + (currYear - currMovie->year);
                connection->weight = edgeWeight;
                currActor->connections.push_back(connection);
                if (use_weighted_edges == true) {
                    pq.push(make_pair(currActor, connection));
                }
            }
        }
        // end of while loop
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* This method reads a file in the format actor<tab>actor2 and adds them into
 * a vector as a pair until it finishes reading all the pairs
 */
bool ActorGraph::pairsToVector(const char* in_filename,
                               vector<pair<string, string>>& actorPairs) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            cerr << "Wrong number cols";
            // we should have exactly 2 columns
            continue;
        }

        string actor(record[0]);
        string actor_2(record[1]);

        // add the actors as pairs into the vector to return
        actorPairs.push_back(make_pair(actor, actor_2));

        // end of while loop
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* This method finds the shortest path from the starting actor to the
 * ending actor on a unweighted edge graph and print the path from the
 * start to the end to a file
 */
int ActorGraph::BFSActors(ActorNode* startingActor, string endingActor,
                          ofstream& out) {
    // to calculate the end node is from start vertex
    // starting actor == endingActor already checked
    startingActor->visited = true;
    // set its own distance to zero
    startingActor->distance = 0;
    queue<Edge*> q;
    MovieNode* dummyNode = new MovieNode("dummyNode", 2019);
    Edge* dummyEdge = new Edge(startingActor, dummyNode);
    q.push(dummyEdge);
    // keep adding dges until end actor is found or all edges have been searched
    // searched
    while (q.empty() == false) {
        Edge* topEdge = q.front();
        // check if ending actor is at top of the queue
        if (topEdge->actor->name == endingActor) {
            // found the ending Actor
            int dist = topEdge->actor->distance;
            ActorGraph::printPath(startingActor, topEdge, out);
            // reset all the actors variables(visited,previous ...etc)
            ActorGraph::resetActorVariables();
            return dist;
        }
        // ending actor is not at the top of queue then
        // add the edges of the actor
        else {
            // get all the edges from this actor into the queue
            ActorNode* currActor = topEdge->actor;
            // the list of edges of the current actor at top of queue
            vector<Edge*> edges = currActor->connections;
            // loop through the edges to add them to the queue
            for (int i = 0; i < edges.size(); i++) {
                //  add the edge to queue only if the actor hasnt been visited
                if (edges[i]->actor->visited == false) {
                    // add the edge to the queue
                    q.push(edges[i]);
                    // remember the previous edge for path finding
                    edges[i]->actor->previous = topEdge;
                    // mark the actor in the edge as visited
                    edges[i]->actor->visited = true;
                    // the offset of the origin
                    edges[i]->actor->distance =
                        edges[i]->actor->previous->actor->distance + 1;
                }
            }
        }

        // pop the top node after getting all the edges
        q.pop();
    }
    ActorGraph::resetActorVariables();
    // dont print anything
    return 0;
}

/* This method find the shortest weighted path from a starting actor to
 * another actor based on the input and returns the total weighted path
 */
pair<Edge*, vector<Edge*>> ActorGraph::shortestPathWeighted(
    ActorNode* startActor, string endActor) {
    const int CURRENT_YEAR = 2019;
    // the pq used for weighted edges
    priority_queue<Edge*, vector<Edge*>, EdgePtrComp> pq;
    vector<Edge*> resetVariables;
    // set these to true since its the first enqued vertex
    startActor->distance = 0;
    // Dummy edge for start
    MovieNode* dummyNode = new MovieNode("dummyNode", 2019);
    Edge* dummyEdge = new Edge(startActor, dummyNode);
    resetVariables.push_back(dummyEdge);
    dummyEdge->distance = 0;
    pq.push(dummyEdge);
    // For each edge in starting at the startActor
    while (pq.empty() == false) {
        Edge* topEdge = pq.top();
        // actor vertex at the top of pq
        ActorNode* topActor = topEdge->actor;
        if (topActor->name == endActor) {
            return make_pair(topEdge, resetVariables);
        }
        pq.pop();
        if (topActor->visited == false) {
            resetVariables.push_back(topEdge);
            topActor->visited = true;
            // loop through each edge of the top actor of the queue
            for (int i = 0; i < topActor->connections.size(); i++) {
                Edge* currEdge = topActor->connections[i];
                int movieYear = currEdge->movie->year;
                int weight = 1 + (CURRENT_YEAR - movieYear);
                // top actor dist + the weight of this edge
                int totalDistance = topActor->distance + weight;
                // if edge from v to w is < w curr distance
                if (totalDistance < currEdge->actor->distance) {
                    currEdge->actor->previous = topEdge;
                    currEdge->actor->distance = totalDistance;
                    currEdge->distance = totalDistance;
                    pq.push(currEdge);
                }
            }
        }
    }
    // return the weighted distance from start -> end
    // assuming the variables were changed from previous algorithm
    return make_pair(dummyEdge, resetVariables);
}

/* This method resets all the instance variables for each character node */
void ActorGraph::resetActorVariables() {
    unordered_map<string, ActorNode*>::iterator itr;
    for (itr = actorsMap.begin(); itr != actorsMap.end(); itr++) {
        itr->second->visited = false;
        itr->second->previous = nullptr;
        itr->second->distance = numeric_limits<int>::max();
        itr->second->parent = nullptr;
        itr->second->size = 1;
    }
}

/* This method prints the path from the starting vertex to ending vertex*/
void ActorGraph::printPath(ActorNode* startActor, Edge* end, ofstream& out) {
    stack<string> stack;
    string path = "";
    string doubleDash = "--";
    string leftIndx = "[";
    string hashAt = "#@";
    string rightIndx = "]";
    string rightArrow = "-->";
    string leftParen = "(";
    string rightParen = ")";
    Edge* currEdge = end;
    // keep looping until it reaches the starting vertex in  backwards direction
    while (currEdge->actor->name != startActor->name) {
        path = doubleDash + leftIndx + currEdge->movie->title + hashAt +
               to_string(currEdge->movie->year) + rightIndx + rightArrow +
               leftParen + currEdge->actor->name + rightParen;
        stack.push(path);
        currEdge = currEdge->actor->previous;
    }
    // add start actor
    path = leftParen + startActor->name + rightParen;
    stack.push(path);

    // print it to the file
    string fullPath = "";
    while (stack.empty() == false) {
        fullPath = fullPath + stack.top();
        stack.pop();
    }
    out << fullPath << endl;
}

/* This method returns the number of movies two actors worked together in */
int commonEdges(Edge* currrEdge, Edge* otherrEdge) {
    ActorNode* currActor = currrEdge->actor;
    vector<Edge*> currActorEdges = currActor->connections;
    int together = 0;
    for (int i = 0; i < currActorEdges.size(); i++) {
        // count how many times curr edge has the other actors name
        if (currActorEdges[i]->actor->name == otherrEdge->actor->name) {
            together++;
        }
    }
    return together;
}

/*This method reads in a file puts the actors into a vector until the EOF */
bool ActorGraph::actorsToVector(const char* in_filename,
                                vector<string>& singleActors) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 1) {
            cerr << "Wrong number cols";
            // we should have exactly 2 columns
            continue;
        }

        string actor(record[0]);
        // add the actors as pairs into the vector to return
        singleActors.push_back(actor);
        // end of while loop
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
/* This method predicts the future collaborations between starting actor
 * and another actor, the first prediction with another one is with someone
 * the starting actor has worked with and the other prediction is with someone
 * the start actor has not collaborated in a movie with
 */
void ActorGraph::linkCollabs(ActorNode* startActor, ofstream& outCollab,
                             ofstream& outUncollab) {
    // vector that holds all the edges from the starting actor to a edge
    vector<Edge*> startActorNeighbors = startActor->connections;
    unordered_map<string, int> edgeMap;

    for (int i = 0; i < startActorNeighbors.size(); i++) {
        // key of the edge
        string edgeName =
            startActor->name + startActorNeighbors[i]->actor->name;
        // the edge doesnt exist
        if (edgeMap.find(edgeName) == edgeMap.end()) {
            edgeMap.insert(make_pair(edgeName, 1));
        }
        // the edge does exist
        else {
            // increment the count
            edgeMap[edgeName] = edgeMap.at(edgeName) + 1;
        }
    }

    priority_queue<ActorNode*, vector<ActorNode*>, ActorPtrComp> pq;
    // to reset the variables
    vector<Edge*> resetVariables;
    startActor->visited = true;
    // First Level
    for (int i = 0; i < startActorNeighbors.size(); i++) {
        // the current edge vertex from startNode -> edgeNode
        Edge* currEdge = startActorNeighbors[i];
        int priority = 0;
        if (currEdge->actor->visited == false) {
            for (int j = 0; j < startActorNeighbors.size(); j++) {
                // dont count its own edge
                Edge* otherEdge = startActorNeighbors.at(j);
                if (currEdge->actor->name != otherEdge->actor->name) {
                    // check # collaborations between start->other edge
                    int moviesTogether = commonEdges(currEdge, otherEdge);
                    priority = priority + moviesTogether;
                }
            }
            currEdge->actor->priority = priority;
            currEdge->actor->visited = true;
            pq.push(currEdge->actor);
            // reset these actor visited variables
            resetVariables.push_back(currEdge);
        }
    }

    // Second level
    priority_queue<ActorNode*, vector<ActorNode*>, ActorPtrComp> pqSecondLevel;
    vector<ActorNode*> toSort;
    int y = 0;
    while (pq.empty() == false) {
        // top edge of the priority queue
        ActorNode* topActor = pq.top();
        // print the top four
        if (y < 4) {
            outCollab << topActor->name << "	";
            y = y + 1;
        }

        for (int i = 0; i < topActor->connections.size(); i++) {
            ActorNode* currActor = topActor->connections[i]->actor;
            if (currActor->visited == false) {
                // calculate the priority
                currActor->priority =
                    currActor->priority +
                    edgeMap.at(startActor->name + topActor->name);
                // to avoid adding the same actor multiple times into the sort
                // vector
                if (currActor->added == false) {
                    currActor->added = true;
                    toSort.push_back(currActor);
                }
            }
        }
        pq.pop();
    }
    // sort the actors based on priorities
    for (int i = 0; i < toSort.size(); i++) {
        pqSecondLevel.push(toSort[i]);
    }
    // print the top four uncollaborated priority actors
    int TOP_FOUR = 4;
    int numPrinted = 0;
    while (pqSecondLevel.empty() == false) {
        if (numPrinted < TOP_FOUR) {
            outUncollab << pqSecondLevel.top()->name << "	";
            pqSecondLevel.pop();
        } else {
            break;
        }
        numPrinted++;
    }

    // reset the actor variables
    for (int i = 0; i < toSort.size(); i++) {
        ActorNode* resetActor = toSort[i];
        resetActor->priority = 0;
        resetActor->added = false;
        resetActor->visited = false;
    }
    for (int i = 0; i < resetVariables.size(); i++) {
        resetVariables[i]->actor->visited = false;
        resetVariables[i]->actor->added = false;
        resetVariables[i]->actor->priority = 0;
    }
    startActor->visited = false;
    startActor->priority = 0;
    startActor->added = false;
    // end method
}
/* This method finds the root of the Actor Node passed in and retuns the root
 * which is defined as the sentinel
 */
ActorNode* ActorGraph::findSentinel(ActorNode* currActor) {
    vector<ActorNode*> collectedNodes;
    ActorNode* actor = currActor;
    while (actor->parent != nullptr) {
        collectedNodes.push_back(actor);
        actor = actor->parent;
    }
    // compress all the collected nodes
    pathCompression(collectedNodes, actor);
    return actor;
}
/* This method compresses the graph by pointing the curr vertex to the sentinel
 * node for a efficent findSentinel time
 */
void ActorGraph::pathCompression(vector<ActorNode*> path, ActorNode* sentinel) {
    /* Make all the nodes in the path point to sentinel as parent */
    for (int i = 0; i < path.size(); i++) {
        ActorNode* toCompress = path.at(i);
        toCompress->parent = sentinel;
    }
}
/* This method connects two edges by connection two Actors vertex together
 * and modifies their size. Returns true if it was succesful
 */
bool ActorGraph::unionActors(ActorNode* actor1, ActorNode* actor2) {
    ActorNode* actor1Sentinel = findSentinel(actor1);
    ActorNode* actor2Sentinel = findSentinel(actor2);
    // only union them if not in the same tree to not create cycles
    if (actor1Sentinel->name != actor2Sentinel->name) {
        // if tree 1 size is <= tree 2 size
        if (actor1Sentinel->size <= actor2Sentinel->size) {
            // update the size
            actor1Sentinel->size = actor1Sentinel->size + actor2Sentinel->size;
            actor2Sentinel->parent = actor1Sentinel;
            return true;
        }
        // if tree 2 size is < tree 1
        else {
            // update the size
            actor2Sentinel->size = actor2Sentinel->size + actor1Sentinel->size;
            actor1Sentinel->parent = actor2Sentinel;
            return true;
        }
    }
    return false;
}
