/* This file contains the Movie Node information which includes the tittle
 * of the movie and the year release.
 *
 * Author: Andres Bernal
 * Sources of Help: Discussion Slides
 */
#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <iostream>
#include <string>

using namespace std;
class ActorNode;
/* This class initialises the movie node with its current arguments*/
class MovieNode {
  public:
    // tittle of the movie
    string title;
    // year that the movie was release
    int year;
    // vector that holds the cast of this movie
    vector<ActorNode*> cast;

    /* The constructor for the Movie Node */
  public:
    MovieNode(string title, int year) : title(title), year(year) {
        cast = vector<ActorNode*>();
    }
};
#endif
