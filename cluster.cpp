#include "cluster.h"

Cluster::Cluster() {}

Cluster::Cluster(Point p) {
    //_points.insert(p);
}



Cluster::Cluster(const std::set<Point> &points) {
    _points.insert(points.begin(), points.end());
}

Cluster::~Cluster() {}


std::set<Cluster> Cluster::sampleDataSet(const std::set<Point> &points) {
    auto dataSet = points;                 // copy data set points
    std::set<Cluster> clusters; // our set of clusters

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
        clusters.emplace(cluster);


    }
    std::cout<< "[DEBUG] End of random sampling. Generated cluster is size  "
             << clusters.size()  << " for total data of size  : " << points.size() << std::endl;
    return clusters;
}

std::ostream &operator<<(std::ostream &out, Cluster &cluster) {
    // TODO
    return out;
}

std::set<Point> Cluster::points() const {
    return _points;
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

////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<bool>> computePM(const std::set<Cluster> &clusters, const std::set<Point> dataSet) {
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
    std::cout << pm.size() << std::endl;
    return pm;
}
std::vector<std::set<Cluster>> extractPSfromPM(const std::set<Cluster> &clusters, const std::vector<std::vector<bool>> &pm) {
    std::vector<Cluster> clustersVect(clusters.begin(), clusters.end());
    std::vector<std::set<Cluster>> preferenceSets;
    int index;
    for(auto psLine : pm) {
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



double jaccard(std::set<Cluster> a, std::set<Cluster> b) {
    std::set<Cluster> u; // union
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(u));

    std::set<Cluster> n; // intersection
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(n));

    return (u.size() - n.size())/static_cast<double>(u.size());

}

void link(std::set<Cluster> &clusters, std::set<Point> &dataSet) {
    std::vector<Cluster> clustersVect(clusters.begin(), clusters.end());

    auto pm = computePM(clusters, dataSet);
    auto preferenceSets = extractPSfromPM(clusters, pm);

    std::pair<Cluster, Cluster> closest;

    int i = 0;
    int j = 0;

    // find closest clusters according to jaccard distance
    for(auto ps1 : preferenceSets) {
        for(auto ps2 : preferenceSets) {
            if(jaccard(ps1, ps2) < 1.) {
                closest = std::make_pair(clustersVect.at(i), clustersVect.at(j));
            }
            j++;
        }
        i++;
    }

    // merge clusters
    std::set_union(closest.first.points().begin(),
                   closest.first.points().begin(),
                   closest.second.points().begin(),
                   closest.second.points().end(),
                   closest.first.points());


}
