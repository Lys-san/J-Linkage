/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-27-2023
 * Last modified : 04-27-2023 */

#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "model.h"
#include "settings.h"
#include <float.h>
#include <Imagine/Graphics.h>


#define INFTY DBL_MAX // approximation of infinity
                      // (isn't really taken into account in calculations)
#define LINE_COLOR Imagine::BLACK


/** Represents a line on the 2D space.
 *  A line is constructed by 2 points but has infinite length.
 *  We work on the finite space [0, 1]x[0, 1].
 *
 *  If displayed on screen, consider that the y axis is going down. */
class Line {
public:
    /** Constructor */
    Line(Point p1, Point p2);

    /** Destructor */
    ~Line();

    /** Stream operator << redefinition. */
    friend std::ostream &operator<<(std::ostream &out, Line &line);

    /** Accessor for private field _a. */
    double a() const;

    /** Accessor for private field _b. */
    double b() const;

    /** Accessor for private field _p1. */
    Point p1() const;

    /** Accessor for private field _p2. */
    Point p2() const;

    /** Returns a randomly selected point from the current line.
     * Guaranties that the returned point is in [0, 1]x[0, 1]. */
    Point randomPoint();

    /** Screen display of a line. */
    void display();

    /** Returns the Minimal Sample Set Size of the model.
     *  For a Line object, this constant is set to 2. */
    int mmss();

    /** Computes and return the consensus set of the model according to the given dataSet*/
    std::set<Point> computeConsensusSet(const std::set<Point> &dataSet);


private:
    Point _p1;      // first point
    Point _p2;      // second point

    // ax + b
    double _a;
    double _b;
};

/** Returns the (shortest) distance from a given point to a given line. */
double distance(Line line, Point point);

#endif // LINE_H
