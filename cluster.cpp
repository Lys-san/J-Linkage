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

bool Cluster::operator<(const Cluster &other) const {
    //return this->_points.size() < other._points.size();
    return this->_points < other._points;
}

bool Cluster::operator==(const Cluster &other) const {
    return this->points() == other.points();
}


//ModelType Cluster::generatePM() {
//    // TODO
//}
