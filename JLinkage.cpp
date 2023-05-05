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

    // cluster generation
    auto clusters = Cluster::sampleDataSet(dataSet);
    // extract models from sampled set
    auto models = extractModels(clusters);
    std::cout << "[DEBUG] Extracted " << models.size() << " models." << std::endl;

    Cluster::displayClusters(clusters);

    // compute PM
    auto pm = computePM(models, dataSet);
    std::cout << "[DEBUG] Computed " << pm.size() << " preference sets" << std::endl;
    std::cout << "[DEBUG] Each PS considers " << pm[0].size() << " models" << std::endl;

    // link until model is found
    auto linkable = true;
    while(linkable) {
        linkable = link(clusters, dataSet, pm, models);
        clearWindow();
        Cluster::displayClustersWithColors(clusters);
    }

    // display model
    validateBiggestCluster(clusters);
    Cluster::displayClusters(clusters);

    std::cout << "Ending with " << clusters.size() << " clusters.";

    Imagine::endGraphics();
    return 0;
}
