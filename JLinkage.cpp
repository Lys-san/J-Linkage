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
    srand((unsigned int)time(0));

    std::set<Point> dataSet;

    // random point generation
    for(int i = 0; i < 40; i++) {
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


    for(int i = 0; i < 60; i++) {
        Point pp = line.randomPoint();
        pp.addNoise();
        std::cout << pp << std::endl;
        pp.display();
        dataSet.emplace(pp);
    }
    std::cout << "[DEBUG] data set of size = " << dataSet.size() << std::endl;



    // cluster generation
    auto clusters = Cluster::sampleDataSet(dataSet);

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
    while(clusters.size() > 1) {
        std::cout << "------------" << std::endl;
        link(clusters, dataSet);

        clearWindow();


        for(auto cluster:clusters) {
            if(cluster.size() > 2) {
                std::cout << "=====" << std::endl;
                std::cout << "cluster of size " << cluster.size() << std::endl;
                std::cout << "=====" << std::endl;
            }

            i++;
            auto col = cols[i % N_COLORS];
            for(auto point : cluster.points()) {
                point.display(col);
            }
        }
    }


    Imagine::endGraphics();
    return 0;
}
