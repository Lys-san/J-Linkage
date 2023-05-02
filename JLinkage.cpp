/** 
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-26-2023
 * Last modified : 04-27-2023
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

    // testing point generation
    for(int i = 0; i < 40; i++) {
        Point p = Point::randomlyGenerated();
        p.display();
        dataSet.emplace(p);
        std::cout << p << std::endl;
    }

    Point p = Point::randomlyGenerated();
    std::cout << p << std::endl;
    dataSet.emplace(p);

    Point q = Point(1, 1);
    std::cout << q << std::endl;
    dataSet.emplace(q);

    Line line = Line(p, q);
    std::cout << line << std::endl;

    //line.display();

    for(int i = 0; i < 60; i++) {
        Point pp = line.randomPoint();
        pp.addNoise();
        std::cout << pp << std::endl;
        pp.display();
        dataSet.emplace(pp);
    }


    Imagine::milliSleep(3000);

    auto clusters = Cluster::sampleDataSet(dataSet);
    Imagine::Color cols[] = COLOR_PACK;
    int i = 0;

    for(auto cluster:clusters) {

        i++;
        auto col = cols[i % N_COLORS];

        // for debug, remove after (or maybe not...?)
        if(cluster.size() == 2) {
            Point p[2];
            int i = 0;
            for(auto point : cluster.points()) {
                p[i++] = point;
            }
            Line line = Line(p[0], p[1]);
            line.display(col);
        }
    }

//    auto cs = line.computeConsensusSet(dataSet);
//    for(auto point : cs) {
//        point.display();
//    }



    Imagine::endGraphics();
    return 0;
}
