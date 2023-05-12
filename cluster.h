/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-27-2023
 * Last modified : 05-12-2023 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <set>

#include "point.h"
#include "model.h"
#include "line.h" // this will be deleted in final version of the code
#include "util.h"


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

    /**
     * Displays the given vectors, automatically assigning each one a color.
     *
     * @param clusters the clusters to be displayed.
     */
    static void displayClusters(const std::vector<Cluster> &clusters);

    /**
     * Displays the given vectors, automatically assigning each one a color.
     *
     * @param clusters the clusters to be displayed.
     */
    static void displayClustersWithColors(const std::vector<Cluster> &clusters);

    /**
     * Displays only the clusters that are validated.
     *
     * @param clusters the clusters to be displayed.
     */
    static void displayValidated(const std::vector<Cluster> &clusters);

    /**
     * @brief displayModels
     * @param clusters
     */
    static void displayModels(const std::vector<Cluster> &clusters);

    // TODO : redo this funcion for generic ModelType model insead of Line
    Line extractLineModel();

    Point extractPointModel();

    /** Computes and returns the intersection of the PS of all the points
     *  contained in the cluster. */
    std::set<Line> computePS(
            const std::set<Point> &dataSet,
            const std::map<Point,
            std::set<Line>> &preferenceSets
            );

    /**
     * Returns the intersection of the two given vectors.
     *
     * @param a first vector
     * @param b second vector
     * @return
     */
    static std::set<Line> makeInter(const std::set<Line> &a,
                                       const std::set<Line> &b
                                       );
    /**
     * @return true if contains a minimum number of points.
     */
    bool isModel();


private:

    // private methods

    /**
     * Returns the union of the two given vectors.
     *
     * @param a first vector
     * @param b second vector
     * @return
     */
    static std::vector<Line> makeUnion(const std::vector<Line> &a,
                                       const std::vector<Line> &b
                                       );



    // attributes

    std::vector<Point> _points;                // vector of points composing the cluster

};

///////////////////////////////////////////////////////////////////////////////////////////

std::map<Point, int> generatePointIndexes();

///** Generates preference matrix from cluster */
//std::vector<std::vector<bool>> computePM(
//        const std::vector<Cluster> &clusters,
//        const std::set<Point> dataSet
//        );

/** Generates preference matrix of data set */
std::vector<std::vector<bool>> computePM(
        const std::vector<Line> &models,
        const std::set<Point> dataSet
        );

/** Returns the transposate of the given pm. */
std::vector<std::vector<bool>> transposatePM(const std::vector<std::vector<bool>> &pm);

/**
 * Exctracts a map associating a point with a set of models from the given PM.
 * Requires a data set and a set of models.
 *
 * @param models
 * @param pm
 * @return
 */
std::map<Point, std::set<Line>> extractPSfromPM(
        const std::set<Point> &dataSet,
        const std::vector<Line> &models,
        const std::vector<std::vector<bool>> &pm);

/** Returns the Jaccard distance (between 0 and 1) from 2 vectors a and b. */
double jaccard(
        std::set<Line> a,
        std::set<Line> b
        );

/** Performs linking action and updates given parameters. */
bool link(
        std::vector<Cluster> &clusters,
        std::set<Point> &dataSet,
        const std::vector<std::vector<bool>> &pm,
        const std::vector<Line> &models
        );

/** (DEPRECATED) Validates the n biggest clusters contained in the given vector. */
void validateNBiggestClusters(unsigned int n, std::vector<Cluster> &clusters);

/** Validates the biggest clusters contained in the given vector. */
void validateBiggestClusters(std::vector<Cluster> &clusters);

/**
 * Extract models from clusters, asserting that cluster contains the number of points required
 * @param clusters
 * @return
 */
std::vector<Line> extractModels(const std::vector<Cluster> &clusters);




#endif // CLUSTER_H
