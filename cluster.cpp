#include "cluster.h"

Cluster::Cluster() {}


Cluster::Cluster(const Cluster& other) {
    for(auto point : other.points()) {
        _points.emplace_back(point);
    }
}

Cluster::Cluster(Point p) {
    //_points.insert(p);
}



Cluster::Cluster(const std::set<Point> &points) {
//    _points.insert(points.begin(), points.end());
    for(auto point : points) {
        _points.emplace_back(point);
    }
}

Cluster::~Cluster() {}


std::vector<Cluster> Cluster::sampleDataSet(const std::set<Point> &points) {
    auto dataSet = points;                 // copy data set points
    std::vector<Cluster> clusters; // our set of clusters

    // building clusters until no more points in data set
    while(dataSet.size() > 0) {
        std::set<Point> clusterPoints;         // will store points from our cluster

        // retrieve a first random point from data set
        auto i = std::rand() % dataSet.size();
        auto it = dataSet.begin();
        std::advance(it, i);
        Point p = *it;
        clusterPoints.emplace(p);
        dataSet.erase(it);

        // TODO : assert that MMSS is <= points.size()
        for(int i = 0; i < std::min(1UL, dataSet.size()); i++) { // TODO : adjust loop acording to ModelType MMSS
            // computing probability according to last selected point
            std::discrete_distribution<> d = p.computeProbabilitiesFor(dataSet);
            std::random_device rd;
            std::mt19937 gen(rd());



            int point_index = d(gen);

            it = dataSet.begin();
            std::advance(it, point_index);
            p = *it;
            clusterPoints.emplace(p);
            dataSet.erase(it);
        }


        auto cluster = Cluster(clusterPoints);
        clusters.emplace_back(cluster);


    }
    std::cout<< "[DEBUG] End of random sampling. Generated cluster is size  "
             << clusters.size()  << " for total data of size  : " << points.size() << std::endl;
    return clusters;
}

std::ostream &operator<<(std::ostream &out, Cluster &cluster) {
    for(auto point : cluster.points()) {
        std::cout << point << std::endl;
    }
    return out;
}

std::vector<Point> Cluster::points() const {
    return _points;
}


void Cluster::addPoint(Point p) {
    _points.emplace_back(p);
}

void Cluster::validate() {
    for(Point &point : _points) {
        point.accept();
    }
}

void Cluster::invalidate() {
    for(auto point : _points) {
        point.reject();
    }
}
int Cluster::size() {
    return _points.size();
}

Line Cluster::extractLineModel() {
    assert(size() == 2);

    // TODO : recode this part better
    Point p[2];
    int i = 0;
    for(auto point : points()) {
        p[i++] = point;
    }
    return Line(p[0], p[1]);
}

Point Cluster::extractPointModel() {
    return *points().begin();
}

bool Cluster::operator<(const Cluster &other) const {
    //return this->_points.size() < other._points.size();
    return this->_points < other._points;
}

bool Cluster::operator==(const Cluster &other) const {
    return this->points() == other.points();
}

std::vector<Cluster> computePS(const std::vector<std::vector<Cluster>> preferenceSets) {
    auto ps = *preferenceSets.begin();
    for(auto clusterSet : preferenceSets) {
        std::set_union(clusterSet.begin(), clusterSet.end(), ps.begin(), ps.end(), std::back_inserter(ps));
    }
    return ps;
}

////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<bool>> computePM(const std::vector<Cluster> &clusters, const std::set<Point> dataSet) {
    //std::vector<std::vector<bool>> pm; // preference matrix
    std::vector<std::vector<bool>> pm(0, std::vector<bool>(0, false));

    for(auto cluster : clusters) {
        if(cluster.size() == 2) {
            auto model = cluster.extractLineModel();
            pm.emplace_back(model.computeBooleanConsensusSet(dataSet));
        }
        else {
            auto model = cluster.extractPointModel();
            pm.emplace_back(model.computeBooleanConsensusSet(dataSet));
        }

    }
    pm = transposatePM(pm);
    return pm;
}
std::vector<std::set<Cluster>> extractPSfromPM(const std::vector<Cluster> &clusters, const std::vector<std::vector<bool>> &pm) {
    std::vector<Cluster> clustersVect(clusters.begin(), clusters.end());
    std::vector<std::set<Cluster>> preferenceSets;
    int index;

    for(auto psLine : pm) {
        index = 0;
        // constructing each ps
        std::set<Cluster> ps;
        for(auto b : psLine) {

            if(b) {
                ps.emplace(clustersVect.at(index));
            }
            index++;
        }
        preferenceSets.emplace_back(ps);
    }
    return preferenceSets;
}

std::vector<std::vector<bool>> transposatePM(const std::vector<std::vector<bool>> &pm) {
    std::vector<std::vector<bool>> transposate(pm.begin()->size(), std::vector<bool>(pm.size(), false));

    for(int i = 0; i < pm.size(); i++) {
        for(int j = 0; j < pm.begin()->size(); j++)
        transposate.at(j).at(i) = pm.at(i).at(j);
    }
    return transposate;
}



double jaccard(std::vector<Cluster> a, std::vector<Cluster> b) {
    if(a == b) {
        return 1.;
    }
    std::vector<Cluster> u; // union
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(u));

    std::vector<Cluster> n; // intersection
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(n));
    return (u.size() - n.size())/static_cast<double>(u.size());

}

bool link(std::vector<Cluster> &clusters, std::set<Point> &dataSet) {
    auto pm = computePM(clusters, dataSet);
    auto preferenceSets = extractPSfromPM(clusters, pm); // vector of sets

    int iFirst = 0;
    int iSecond = 0;
    double minDist = 1.;
    bool linkable = false;


    // find closest clusters according to jaccard distance
    for(auto c1 : clusters) {
        // TODO (?) : put the following code (cluster PS computing) in a function
        // compute c1's PS
        std::vector<std::vector<Cluster>> c1PointsPs;
        for(auto point : c1.points()) {
            // we assume that the point is contained in the dataSet...
            int pointIndex = std::distance(dataSet.begin(), dataSet.find(point));
            std::vector<Cluster> tmp(preferenceSets.at(pointIndex).begin(), preferenceSets.at(pointIndex).end());
            c1PointsPs.emplace_back(tmp);
        }
        // do the intersection
        std::vector<Cluster> ps1 = c1PointsPs.at(0); // asume that we have at least 1 point
        for(std::vector<Cluster> ps : c1PointsPs) {
            std::set_intersection(
                        ps.begin(),
                        ps.end(),
                        ps1.begin(),
                        ps1.end(),
                        std::back_inserter(ps1)
                        );
        }


        // for each other buffer
        for(auto c2 : clusters) {
            // compute c2's PS
            std::vector<std::vector<Cluster>> c2PointsPs;
            for(auto point : c2.points()) {
                // we assume that the point is contained in the dataSet...
                int pointIndex = std::distance(dataSet.begin(), dataSet.find(point));
                std::vector<Cluster> tmp(preferenceSets.at(pointIndex).begin(), preferenceSets.at(pointIndex).end());
                c2PointsPs.emplace_back(tmp);
            }
            // do the intersection
            std::vector<Cluster> ps2 = c2PointsPs.at(0); // asume that we have at least 1 point
            for(auto ps : c2PointsPs) {
                std::set_intersection(
                            ps.begin(),
                            ps.end(),
                            ps1.begin(),
                            ps1.end(),
                            std::back_inserter(ps2)
                            );
            }
            // compare
            auto dist = jaccard(ps1, ps2);
            if(dist < 1. && dist < minDist && !(c1 == c2)) {
                iFirst = std::find(clusters.begin(), clusters.end(), c1) - clusters.begin();
                iSecond = std::find(clusters.begin(), clusters.end(), c2) - clusters.begin();
                linkable = true;
            }
        }
    }

    // merge clusters
    if(linkable) {
        Cluster &mergingCluster = clusters[iFirst];

        for(auto point : clusters[iSecond].points()) {
            mergingCluster.addPoint(point);
        }
        auto it2 = std::find(clusters.begin(), clusters.end(), clusters[iSecond]);

        clusters.erase(it2);
    }
    return linkable;
}

Cluster findBiggest(const std::vector<Cluster> &clusters) {
    assert(clusters.size() > 0);
    Cluster biggest = clusters[0];
    for(auto cluster : clusters) {
        if(cluster.size() > biggest.size()) {
            biggest = cluster;
        }
    }
    return biggest;
}
