/** 
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-26-2023
 * Last modified : 05-05-2023
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


    // random point generation
    auto dataSet = Point::generateRandomDataSetOfSize(N_OUTLIERS);

    // model with noise
    auto inliers = Line::randomlyGenerated().generateRandomInliers(N_INLIERS);
    dataSet.insert(inliers.begin(), inliers.end());

    std::cout << "[DEBUG] data set of size = " << dataSet.size() << std::endl;
    Point::displayPoints(dataSet);

    // cluster generation
    auto clusters = Cluster::sampleDataSet(dataSet);
    // extract models from sampled set
    auto models = extractModels(clusters);


//    // compute PM
//    auto pm = computePM(models, dataSet);

//    Imagine::Color cols[] = COLOR_PACK;
//    int i = 0;

//    for(auto cluster:clusters) {
//        i++;
//        auto col = cols[i % N_COLORS];
//        for(auto point : cluster.points()) {
//            point.display(col);
//        }

//        // for debug, remove after (or maybe not...?)
//        if(cluster.size() == 2) {
//            Point p[2];
//            int i = 0;
//            for(auto point : cluster.points()) {
//                p[i++] = point;
//            }
//            Line line = Line(p[0], p[1]);
//        }
//    }

//    double avg = 0.;
//    auto linkable = true;
//    int index = 0;
//    while(linkable) {
//        std::cout << "link index : " << index++ << std::endl;
//        linkable = link(clusters, dataSet, pm, models);
//        if(!linkable) {
//            std::cout << "HERE" << std::endl;
//        }
//        clearWindow();


//        for(auto cluster:clusters) {
//            i++;
//            auto col = cols[i % N_COLORS];
//            for(auto point : cluster.points()) {
//                point.display(col);
//            }
//        }
//    }

//    auto model = findBiggest(clusters);
//    model.validate();
//    for(auto cluster : clusters) {
//        if(cluster == model) {
//            cluster.validate();
//        }

//        for(auto point : cluster.points()) {
//            point.display();
//        }
//    }

//    std::cout << "Ending with " << clusters.size() << " clusters.";




    Imagine::endGraphics();
    return 0;
}
