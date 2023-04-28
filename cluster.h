/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-27-2023
 * Last modified : 04-28-2023 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <set>

#include "point.h"
#include "model.h"


/** Represents a cluster of points, which can eventually be view as a model hypothesis.
 *  A cluster is a set of points from the 2D space. */
class Cluster {
public:
    /** Constructors */
    Cluster();

    Cluster(Point p);

    Cluster(const std::set<Point> &points);

    /** Destructor */
    ~Cluster();

    /** Factory method that generates M clusters from the given data set. */
    static std::set<Cluster> sampleDataSet(const std::set<Point> &points);

    /**
     * < operator redefinition for Cluster objects.
     *
     * @param other the comparing cluster.
     * @return true if the current cluster is < than the other.
     */
    bool operator<(const Cluster &other) const;

    /**
     * == operator redefinition for Cluster objects.
     *
     * @param other
     * @return
     */
    bool operator==(const Cluster &other) const;

    /** Accessor for private _points field. */
    std::set<Point> points() const;

    /** Returns the size of the cluster, i.e. the number of elements
     *  that it contains. */
    int size();

    /** Generate preference matrix from cluster */
   // ModelType generatePM();


private:

    std::set<Point> _points;                   // set of points composing the cluster
    std::set<Point> _consensusSet;             // set of points that matches with the model
                                               // (aren't necessarely inside the set
                                               // of points composing the cluster)
    bool _preferenceSet[MAX_POINTS_ON_SCREEN]; // preference set of the cluster
};

#endif // CLUSTER_H
