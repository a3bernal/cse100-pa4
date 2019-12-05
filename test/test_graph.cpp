#include <gtest/gtest.h>
#include <iostream>
#include <queue>
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
        MovieNode* movie1 = new MovieNode("1", 2015);
        MovieNode* movie2 = new MovieNode("2", 2016);
        MovieNode* movie3 = new MovieNode("3", 2012);
        MovieNode* movie4 = new MovieNode("4", 2017);
        // same name as 4 but different year to test this edge case
        MovieNode* movie5 = new MovieNode("4", 2018);
        MovieNode* movie6 = new MovieNode("6", 2011);
        MovieNode* movie7 = new MovieNode("7", 2013);
        MovieNode* movie8 = new MovieNode("8", 2010);

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
        myGraph.moviesMap.insert(
            make_pair(movie7->title + to_string(movie7->year), movie7));
        myGraph.moviesMap.insert(
            make_pair(movie8->title + to_string(movie8->year), movie8));

        // create the graph edges
        // a ->b
        Edge* ab = new Edge(b, movie1);
        ab->weight = 5;
        // a->d
        Edge* ad = new Edge(d, movie4);
        ad->weight = 3;
        // b->a
        Edge* ba = new Edge(a, movie1);
        ba->weight = 5;
        // Edge b->c
        Edge* bc = new Edge(c, movie2);
        bc->weight = 4;
        // Edge b->d
        Edge* bd = new Edge(d, movie8);
        bd->weight = 10;
        // Edge b->e
        Edge* be = new Edge(e, movie7);
        be->weight = 7;
        // edge c->b
        Edge* cb = new Edge(b, movie2);
        cb->weight = 4;
        // edge c->e
        Edge* ce = new Edge(e, movie6);
        ce->weight = 9;
        // edge d->a
        Edge* da = new Edge(a, movie4);
        da->weight = 3;
        // edge d->b
        Edge* db = new Edge(b, movie8);
        db->weight = 10;
        // edge d->e
        Edge* de = new Edge(e, movie5);
        de->weight = 2;
        // edge e->b
        Edge* eb = new Edge(b, movie7);
        eb->weight = 7;
        // edge e->d
        Edge* ed = new Edge(d, movie5);
        ed->weight = 2;
        // edge e->c
        Edge* ec = new Edge(c, movie6);
        ec->weight = 9;

        myGraph.pq.push(make_pair(d, de));
        myGraph.pq.push(make_pair(e, ed));

        myGraph.pq.push(make_pair(a, ad));
        myGraph.pq.push(make_pair(d, da));

        myGraph.pq.push(make_pair(b, bc));
        myGraph.pq.push(make_pair(c, cb));

        myGraph.pq.push(make_pair(a, ab));
        myGraph.pq.push(make_pair(b, ba));

        myGraph.pq.push(make_pair(b, be));
        myGraph.pq.push(make_pair(e, eb));

        myGraph.pq.push(make_pair(c, ce));
        myGraph.pq.push(make_pair(e, ec));

        myGraph.pq.push(make_pair(b, bd));
        myGraph.pq.push(make_pair(d, db));

        // connect their edges
        a->connections.push_back(ab);
        a->connections.push_back(ad);

        b->connections.push_back(ba);
        b->connections.push_back(bc);
        b->connections.push_back(bd);
        b->connections.push_back(be);

        c->connections.push_back(cb);
        c->connections.push_back(ce);

        d->connections.push_back(da);
        d->connections.push_back(db);
        d->connections.push_back(de);

        e->connections.push_back(eb);
        e->connections.push_back(ed);
        e->connections.push_back(ec);
    }
};

TEST_F(SimpleGraphFixture, testMovieTraveler) {
    ActorNode* start = myGraph.pq.top().first;
    ASSERT_EQ(start->name, "d");
    ActorNode* end = myGraph.pq.top().second->actor;
    bool add = myGraph.unionActors(start, end);
    ASSERT_EQ(add, true);
    myGraph.pq.pop();

    ActorNode* start1 = myGraph.pq.top().first;
    ASSERT_EQ(start1->name, "e");
    ActorNode* end1 = myGraph.pq.top().second->actor;
    ASSERT_EQ(end1->name, "d");
    bool add1 = myGraph.unionActors(start1, end1);
    ASSERT_EQ(add1, false);
    myGraph.pq.pop();

    ActorNode* start2 = myGraph.pq.top().first;
    ASSERT_EQ(start2->name, "a");
    ActorNode* end2 = myGraph.pq.top().second->actor;
    ASSERT_EQ(end2->name, "d");
    bool add2 = myGraph.unionActors(start2, end2);
    ASSERT_EQ(add2, true);
}
