/** 
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-26-2023
 * Last modified : 05-03-2023
 * 
 * Implementation of the J-linkage algorithm for multi-model estimation.
 * Using the Imagine++ library.
 * 
 * Inspired by R. Toldo and A. Fusiello work on 'Robust Multiple Structure
 * Estimation with J-linkage'. */

#include <iostream>
#include "point.h"
#include "line.h"
#include "cluster.h"
using namespace std;


int main() {
    Imagine::openWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    // seed initialization
    srand((unsigned int)time(0)); // uncomment this line after debugging
//    srand(0); // for debug

    std::set<Point> dataSet;

    // random point generation
    for(int i = 0; i < N_OUTLIERS; i++) {
        Point p = Point::randomlyGenerated();
        p.display();
        dataSet.emplace(p);
    }

    // model with noise
    Point p = Point::randomlyGeneratedOnYvalue(0.);
    std::cout << "[DEBUG] p = " << p << std::endl;
    dataSet.emplace(p);

    Point q = Point::randomlyGeneratedOnYvalue(1.);
    std::cout << "[DEBUG] q = " << q << std::endl;

    dataSet.emplace(q);

    Line line = Line(p, q);

    //line.display();


    for(int i = 0; i < N_INLIERS; i++) {
        Point pp = line.randomPoint();
        pp.addNoise();
        pp.display();
        dataSet.emplace(pp);
    }
    std::cout << "[DEBUG] data set of size = " << dataSet.size() << std::endl;



    // cluster generation
    auto clusters = Cluster::sampleDataSet(dataSet);
    // extract models
    auto models = extractModels(clusters);
    // compute PM
    auto pm = computePM(models, dataSet);

    Imagine::Color cols[] = COLOR_PACK;
    int i = 0;

    for(auto cluster:clusters) {
        i++;
        auto col = cols[i % N_COLORS];
        for(auto point : cluster.points()) {
            point.display(col);
        }

        // for debug, remove after (or maybe not...?)
        if(cluster.size() == 2) {
            Point p[2];
            int i = 0;
            for(auto point : cluster.points()) {
                p[i++] = point;
            }
            Line line = Line(p[0], p[1]);
        }
    }

    double avg = 0.;
    auto linkable = true;
    int index = 0;
    while(linkable) {
        std::cout << "link index : " << index++ << std::endl;
        linkable = link(clusters, dataSet, pm, models);
        if(!linkable) {
            std::cout << "HERE" << std::endl;
        }
        clearWindow();


        for(auto cluster:clusters) {
            i++;
            auto col = cols[i % N_COLORS];
            for(auto point : cluster.points()) {
                point.display(col);
            }
        }
    }

    auto model = findBiggest(clusters);
    model.validate();
    for(auto cluster : clusters) {
        if(cluster == model) {
            cluster.validate();
        }

        for(auto point : cluster.points()) {
            point.display();
        }
    }

    std::cout << "Ending with " << clusters.size() << " clusters.";




    Imagine::endGraphics();
    return 0;
}
