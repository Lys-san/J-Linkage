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

    // models with noise
    for(auto i = 0; i < N_MODELS; i++) {
        auto inliers = Line::randomlyGenerated().generateRandomInliers(N_INLIERS);
        dataSet.insert(inliers.begin(), inliers.end());
    }

//    // FOR DEBUG, REMOVE AFTER
//    for(auto point : dataSet) {
//        point.display();
//    }



    // cluster generation
    auto clusters = Cluster::sampleDataSet(dataSet);
    // extract models from sampled set
    auto models = extractModels(clusters);
    std::cout << "[DEBUG] Extracted " << models.size() << " models :" << std::endl;
    for(auto model : models) {
        std::cout << model << std::endl;
    }

    Cluster::displayClusters(clusters);
    // FOR DEBUG, displaying how points are sampled with lines
//    for(auto cluster : clusters) {
//        if(cluster.size() == 2) {
//            cluster.extractLineModel().display();
//            std::cout << "[DEBUG] : distance between sampled points : " << cluster.extractLineModel().squaredLength() << std::endl;
//        }
//    }

    // compute PM
    auto pm = computePM(models, dataSet); // the PM *looks* ok
    std::cout << "[DEBUG] Computed " << pm.size() << " preference sets" << std::endl;
    std::cout << "[DEBUG] Each PS considers " << pm[0].size() << " models" << std::endl;

    // uncomment for PM display
//    std::cout << "-----------" << std::endl;
//    for(auto line : pm) {
//        for(auto value : line) {
//            std::cout << value << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "-----------" << std::endl;

    std::cout << "[DEBUG] Linking clusters, please wait... " << std::endl;


    // link until model is found
    auto linkable = true;
    int linkIndex = 0;
    while(linkable) {
        linkIndex++;
        linkable = link(clusters, dataSet, pm, models);
        clearWindow();
//        Cluster::displayClustersWithColors(clusters);
    }

    // display model
//    Cluster::displayClusters(clusters);
    clearWindow();

    validateNBiggestClusters(N_MODELS, clusters);
    auto resWindow = Imagine::openWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "results", 330, 10);
    Imagine::setActiveWindow(resWindow);
//    Cluster::displayClustersWithColors(clusters);
    Cluster::displayValidated(clusters);

//    clearWindow();

//    Cluster::displayClusters(clusters);

    std::cout << "Ending with " << clusters.size() << " clusters after " << linkIndex << " linkages." << std::endl;

    Imagine::endGraphics();
    return 0;
}
