/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-27-2023
 * Last modified : 05-04-2023 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <set>

#include "point.h"
#include "model.h"
#include "line.h" // this will be deleted in final version of the code


/** Represents a cluster of points, which can eventually be view as a model hypothesis.
 *  A cluster is a set of points from the 2D space. */
class Cluster {
public:
    /** Constructors */
    Cluster();

    Cluster(const Cluster& other);

    Cluster(Point p);

    Cluster(const std::set<Point> &points);

    /** Destructor */
    ~Cluster();

    /** Factory method that generates M clusters from the given data set. */
    static std::vector<Cluster> sampleDataSet(const std::set<Point> &points);

    /** Stream operator << redefinition. */
    friend std::ostream &operator<<(std::ostream &out, Cluster &cluster);

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
    std::vector<Point> points() const;

    /** Adds point to cluster. */
    void addPoint(Point p);

    /** Accepts all points. */
    void validate();

    /** Rejects all points. */
    void invalidate();

    /** Returns the size of the cluster, i.e. the number of elements
     *  that it contains. */
    int size();

    // TODO : redo this funcion for generic ModelType model insead of Line
    Line extractLineModel();

    Point extractPointModel();

    /** Computes and returns the intersection of the PS of all the points
     *  contained in the cluster. */
    std::vector<Cluster> computePS(const std::vector<std::vector<Cluster>> preferenceSets);

private:

    std::vector<Point> _points;                // vector of points composing the cluster

};

std::map<Point, int> generatePointIndexes();

/** Generates preference matrix from cluster */
std::vector<std::vector<bool>> computePM(const std::vector<Cluster> &clusters, const std::set<Point> dataSet);

/** Returns the transposate of the given pm. */
std::vector<std::vector<bool>> transposatePM(const std::vector<std::vector<bool>> &pm);

std::vector<std::set<Cluster>> extractPSfromPM(const std::vector<Cluster> &clusters, const std::vector<std::vector<bool>> &pm);

/** Returns the Jaccard distance (between 0 and 1) from 2 vectors a and b. */
double jaccard(std::vector<Cluster> a, std::vector<Cluster> b);

/** Performs linking action and updates given parameters. */
bool link(std::vector<Cluster> &clusters, std::set<Point> &dataSet);

/** Returns a copy of the biggest cluster contained in the given vector. */
Cluster findBiggest(const std::vector<Cluster> &clusters);

#endif // CLUSTER_H
