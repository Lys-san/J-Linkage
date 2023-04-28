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
        std::cout<< "[DEBUG] Extacting point " << p << std::endl;
//        std::cout<< "[DEBUG] Data set has now size " << dataSet.size() << std::endl;
        clusterPoints.emplace(p);
        dataSet.erase(it);

        // TODO : assert that MMSS is <= points.size()
        for(int i = 0; i < std::min(1UL, dataSet.size()); i++) { // TODO : adjust loop acording to ModelType MMSS
            // computing probability according to last selected point
            std::discrete_distribution<> d = p.computeProbabilitiesFor(dataSet);
            std::random_device rd;
            std::mt19937 gen(rd());



            int point_index = d(gen);
            std::cout<< "[DEBUG] Random : " << point_index << std::endl;

            it = dataSet.begin();
            std::advance(it, point_index);
            p = *it;
            clusterPoints.emplace(p);
        }

        std::cout << "[DEBUG]  ----------- created cluser : " << std::endl;
        for(auto point: clusterPoints) {
            std::cout<< "[DEBUG] Point : " << point << std::endl;
        }
        std::cout << "[DEBUG]  ----------- " << std::endl;

        auto cluster = Cluster(clusterPoints);
        auto res = clusters.emplace(cluster);

        std::cout << "[DEBUG] " << (clusters.find(cluster) != clusters.end()) << std::endl;
        std::cout << "[DEBUG] EMPLACE RETURN VAL =  " << res.second << std::endl;

        std::cout << "[DEBUG]  ----------- Is similar to : " << std::endl;
        for(auto point: clusters.find(cluster)->points()) {
            std::cout<< "[DEBUG] Point : " << point << std::endl;
        }
        std::cout << "[DEBUG]  ----------- " << std::endl;

        for(auto c:clusters) {
            if(c == cluster) {
                std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;

            }
        }

        std::cout << "[DEBUG] Emplacing cluster of size " << cluster.size() << std::endl;
        std::cout << "[DEBUG] Cluster set now contains " << clusters.size() << " clusters." << std::endl;

    }
    std::cout<< "[DEBUG] End of random sampling. Generated cluster is size  "
             << clusters.size()  << " for total data of size  : " << points.size() << std::endl;
    return clusters;
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
