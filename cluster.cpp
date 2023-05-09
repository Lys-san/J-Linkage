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
    std::cout<< "[DEBUG] End of random sampling. Generated "
             << clusters.size()  << " clusters for total data of size  : " << points.size() << std::endl;
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

void Cluster::displayClusters(const std::vector<Cluster> &clusters) {
    for(auto cluster:clusters) {
        for(auto point : cluster.points()) {
            point.display();
        }
    }
}

void Cluster::displayClustersWithColors(const std::vector<Cluster> &clusters) {
    Imagine::Color cols[] = COLOR_PACK;
    int i = 0;

    for(auto cluster:clusters) {
        i++;
        auto col = cols[i % N_COLORS];
        for(auto point : cluster.points()) {
            point.display(col);
        }
    }
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

std::set<Line> Cluster::computePS(const std::set<Point> &dataSet, const std::map<Point, std::set<Line>> &preferenceSets) {
    std::vector<std::set<Line>> clustersPointsPS;
    std::cout << "[DEBUG] before inter ------ " << std::endl;

    for(auto point : _points) {
        auto ps = preferenceSets.at(point);

        std::cout << "Point "<< point << " fits with models : " << std::endl;


        clustersPointsPS.emplace_back(ps);
        for(auto model : ps) {
            std::cout << model << std::endl;
        }
        std::cout << std::endl;


    }
    std::cout << "------------- " << std::endl;

    // intersection
    std::set<Line> inter = clustersPointsPS[0];
    std::set<Line> res;
    for(auto ps : clustersPointsPS) {
        std::set_intersection(
                    ps.begin(),
                    ps.end(),
                    inter.begin(),
                    inter.end(),
                    std::inserter(res, res.begin())
                    );
        inter.clear();
        inter.insert(res.begin(), res.end());
    }

    std::cout << "[DEBUG] afer inter ------ " << std::endl;
    for(auto model : inter) {
        std::cout << model << std::endl;
    }
    std::cout << "------------- " << std::endl;


    return inter;
}

////////////////////////////////////////////////////////////////////////////////////

//std::vector<Line> Cluster::makeUnion(const std::vector<Line> &a, const std::vector<Line> &b) {
//    std::vector<Line> res;

//}

////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<bool>> computePM(const std::vector<Line> &models, const std::set<Point> dataSet) {
    std::vector<std::vector<bool>> pm(0, std::vector<bool>(0, false));

    for(auto model : models) {
        pm.emplace_back(model.computeBooleanConsensusSet(dataSet));
    }
    pm = transposatePM(pm);
    return pm;
}

std::map<Point, std::set<Line>> extractPSfromPM(const std::set<Point> &dataSet, const std::vector<Line> &models, const std::vector<std::vector<bool>> &pm) {
    std::map<Point, std::set<Line>> preferenceSets;

    int pointIndex;
    int modelIndex;

    pointIndex = 0;
    for(auto psLine : pm) { // loop on rows (points)
        modelIndex = 0;
        auto pointIterator = dataSet.begin();
        std::advance(pointIterator, pointIndex);

        // constructing each ps
        std::set<Line> ps;
        auto val = *pointIterator;
        std::cout << "Computing PS for point " << val << std::endl;
        for(auto b : psLine) { // loop on columns (models)

            if(b) {
                auto tmp = models.at(modelIndex);
                std::cout << "Inserting " << tmp << std::endl; // values look oK

                if(ps.insert(models.at(modelIndex)) .second == false) { // the problem is that somehow, computer thinks that the element is alread present
                    std::cout << "NOT INSERTED" << std::endl;
            }
            }
            modelIndex++;
        }
        pointIndex++;
        preferenceSets.emplace(std::make_pair(*pointIterator, ps));
    }
    std::cout << "[DEBUG] computed preference sets : " << std::endl;
    for(auto ps : preferenceSets) {
        auto p = ps.first;
        std::cout << "for point " << p << std::endl;

        for(auto model : ps.second) {
            std::cout << model << std::endl;
        }
        std::cout << std::endl;
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



double jaccard(std::set<Line> a, std::set<Line> b) {
    if(a == b) {
        return 1.;
    }
    std::vector<Line> u; // union
//    std::cout << "a-------" << std::endl;
//    for(auto line : a) {
//        std::cout << line << std::endl;
//    }
//    std::cout << "-------" << std::endl;

//    std::cout << "b-------" << std::endl;
//    for(auto line : b) {
//        std::cout << line << std::endl;
//    }
//    std::cout << "-------" << std::endl;

    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(u));

//    std::cout << "union-------" << std::endl;
//    for(auto line : u) {
//        std::cout << line << std::endl;
//    }
//    std::cout << "-------" << std::endl;

    std::vector<Line> n; // intersection

//    std::cout << "in,ter-------" << std::endl;
//    for(auto line : n) {
//        std::cout << line << std::endl;
//    }
//    std::cout << "-------" << std::endl;
//    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(n));
//    return (u.size() - n.size())/static_cast<double>(u.size());
    return 0.;

}

bool link(std::vector<Cluster> &clusters,
          std::set<Point> &dataSet,
          const std::vector<std::vector<bool>> &pm,
          const std::vector<Line> &models
          ) {

    auto preferenceSets = extractPSfromPM(dataSet, models, pm); // map of point/set

    int iFirst     = 0;     // index of first cluster to link
    int iSecond    = 0;     // index of second cluster to link
    double minDist = 1.;    // min. distance between clusters PS (default : 1.)
    bool linkable  = false; // do we apply link operation on clusters or not


    // find closest clusters according to jaccard distance
    for(auto c1 : clusters) {
        auto ps1 = c1.computePS(dataSet, preferenceSets); // TODO : find out why PS has duplicates
        // for each other buffer
        for(auto c2 : clusters) {
            std::cout << "[DEBUG] on cluser : " << std::endl;
            for(auto point : c2.points()) {
                std::cout << point << " ";
            }
            std::cout << std::endl;

            auto ps2 = c2.computePS(dataSet, preferenceSets);

            // compare
            auto dist = jaccard(ps1, ps2);

            std::cout << "jaccard = " << dist << std::endl;

            if(dist < minDist) {
                iFirst = std::find(clusters.begin(), clusters.end(), c1) - clusters.begin();
                iSecond = std::find(clusters.begin(), clusters.end(), c2) - clusters.begin();
                linkable = true;
            }
        }
    }

    if(linkable) {
        // merge clusters
        Cluster &mergingCluster = clusters[iFirst];

        for(auto point : clusters[iSecond].points()) {
            mergingCluster.addPoint(point);
        }
        auto it = std::find(clusters.begin(), clusters.end(), clusters[iSecond]);
        clusters.erase(it);
    }
    return linkable;
}

void validateBiggestCluster(std::vector<Cluster> &clusters) {
    assert(clusters.size() > 0);
    auto it = std::max_element(clusters.begin(), clusters.end());
    it->validate();
}

std::vector<Line> extractModels(const std::vector<Cluster> &clusters) {
    std::vector<Line> models;
    for(auto cluster : clusters) {
        if(cluster.size() == 2) {
            models.emplace_back(cluster.extractLineModel());
        }
    }
    return models;
}


