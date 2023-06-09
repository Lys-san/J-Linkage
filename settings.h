/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-28-2023
 * Last modified : 05-12-2023
 *
 * Global parameters for J-Linkage algorithm. */

#ifndef SETTINGS_H
#define SETTINGS_H



#define EPSILON       0.03       // threshold for consensus set computing
#define Z             1          // normalization constant (in fact, we can keep it to 1)
#define SQUARED_SIGMA 0.001      // for random sampling
#define MAX_NOISE     0.005      // max value added to an inlier to ennoise the model (default : 0.01)


#define COLOR_PACK {Imagine::GREEN,   \
                    Imagine::RED,    \
                    Imagine::BLUE,    \
                    Imagine::ORANGE,  \
                    Imagine::PURPLE,  \
                    Imagine::BLACK,     \
                    Imagine::YELLOW   \
                    } // color pack for clusters display (7 colors)

// adjust these parameters for testing
#define N_MODELS      5   // nuber of models
#define N_INLIERS     15 // inliers for 1 model
#define N_OUTLIERS    5 // in general data set



#define N_COLORS 9

#endif // SETTINGS_H
