#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "ActorGraph.cpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Edge.hpp"
#include "MovieNode.hpp"

class ActorGraph;
using namespace std;
using namespace testing;

class SimpleGraphFixture : public ::testing::Test {
  public:
    ActorGraph myGraph;

  public:
    SimpleGraphFixture() {
        // the actor nodes
        ActorNode* a = new ActorNode("a");
        ActorNode* b = new ActorNode("b");
        ActorNode* c = new ActorNode("c");
        ActorNode* d = new ActorNode("d");
        ActorNode* e = new ActorNode("e");
        ActorNode* f = new ActorNode("f");

        // the movie nodes
        MovieNode* movie1 = new MovieNode("1", 2019);
        MovieNode* movie2 = new MovieNode("2", 2019);
        MovieNode* movie3 = new MovieNode("3", 2019);
        MovieNode* movie4 = new MovieNode("4", 2019);
        // same name as 4 but different year to test this edge case
        MovieNode* movie5 = new MovieNode("4", 2018);
        MovieNode* movie6 = new MovieNode("6", 2018);
        MovieNode* movie7 = new MovieNode("7", 2018);
        MovieNode* movie8 = new MovieNode("8", 2018);

        // put the actors in the hashmap
        unordered_map<string, ActorNode*> actorsMAP;
        myGraph.actorsMap.insert(make_pair("a", a));
        myGraph.actorsMap.insert(make_pair("b", b));
        myGraph.actorsMap.insert(make_pair("c", c));
        myGraph.actorsMap.insert(make_pair("d", d));
        myGraph.actorsMap.insert(make_pair("e", e));
        myGraph.actorsMap.insert(make_pair("f", f));

        // put the movies in their hashmap
        myGraph.moviesMap.insert(
            make_pair(movie1->title + to_string(movie1->year), movie1));
        myGraph.moviesMap.insert(
            make_pair(movie2->title + to_string(movie2->year), movie2));
        myGraph.moviesMap.insert(
            make_pair(movie3->title + to_string(movie3->year), movie3));
        myGraph.moviesMap.insert(
            make_pair(movie4->title + to_string(movie4->year), movie4));
        myGraph.moviesMap.insert(
            make_pair(movie5->title + to_string(movie5->year), movie5));
        myGraph.moviesMap.insert(
            make_pair(movie6->title + to_string(movie6->year), movie6));

        // create the graph edges
        // a ->b
        Edge* ab = new Edge(b, movie1);
        Edge* ab2 = new Edge(b, movie6);
        // a->d
        Edge* ad = new Edge(d, movie4);
        // b->a
        Edge* ba = new Edge(a, movie1);
        Edge* ba2 = new Edge(a, movie6);
        // Edge b->c
        Edge* bc = new Edge(c, movie2);
        // Edge b->d
        Edge* bd = new Edge(d, movie3);
        // Edge b->e
        Edge* be = new Edge(e, movie3);
        // edge c->b
        Edge* cb = new Edge(b, movie2);
        // edge d->a
        Edge* da = new Edge(a, movie4);
        // edge d->b
        Edge* db = new Edge(b, movie3);
        // edge d->e
        Edge* de = new Edge(e, movie3);
        // edge e->b
        Edge* eb = new Edge(b, movie3);
        // edge e->d
        Edge* ed = new Edge(d, movie3);
        // edge e->f
        Edge* ef = new Edge(f, movie5);
        // edge f->e
        Edge* fe = new Edge(e, movie5);

        // connect their edges
        a->connections.push_back(ab);
        a->connections.push_back(ab2);
        a->connections.push_back(ad);

        b->connections.push_back(ba);
        b->connections.push_back(ba2);
        b->connections.push_back(bc);
        b->connections.push_back(bd);
        b->connections.push_back(be);

        c->connections.push_back(cb);

        d->connections.push_back(da);
        d->connections.push_back(db);
        d->connections.push_back(de);

        e->connections.push_back(eb);
        e->connections.push_back(ed);
        e->connections.push_back(ef);

        f->connections.push_back(fe);
    }
};

/*
TEST_F(SimpleGraphFixture, testBFSTriangle) {

ActorNode* start = myGraph.actorsMap.at("b");
string end = "c";
int distance = myGraph.BFSActors(start, end);
ASSERT_EQ(1, distance);

start = myGraph.actorsMap.at("b");
end = "d";
distance = myGraph.BFSActors(start, end);
ASSERT_EQ(1, distance);

start = myGraph.actorsMap.at("b");
end = "f";
distance = myGraph.BFSActors(start, end);
ASSERT_EQ(2, distance);

start = myGraph.actorsMap.at("f");
end = "a";
distance = myGraph.BFSActors(start, end);
ASSERT_EQ(3, distance);

}*/

/*
TEST_F(SimpleGraphFixture, testPredictor) {

ActorNode* start = myGraph.actorsMap.at("b");
vector<Edge*> check = myGraph.actorCommonNeighbors(start);
// d , a , e, c
ASSERT_EQ(check[0]->actor->name, "d");
ASSERT_EQ(check[0]->priority, 3);

ASSERT_EQ(check[1]->actor->name, "a");
ASSERT_EQ(check[1]->priority, 1);

ASSERT_EQ(check[2]->actor->name, "e");
ASSERT_EQ(check[2]->priority, 1);

ASSERT_EQ(check[3]->actor->name, "c");
ASSERT_EQ(check[3]->priority, 0);

}*/
