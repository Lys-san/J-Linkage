/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-28-2023
 * Last modified : 05-10-2023
 *
 * Global parameters for J-Linkage algorithm. */

#ifndef SETTINGS_H
#define SETTINGS_H



#define EPSILON       0.1   // threshold for consensus set computing
#define Z             1      // normalization constant
#define SQUARED_SIGMA 0.01      // for random sampling

#define COLOR_PACK {Imagine::RED,   \
                    Imagine::GREEN,    \
                    Imagine::CYAN,    \
                    Imagine::BLUE,   \
                    Imagine::MAGENTA, \
                    Imagine::ORANGE,  \
                    Imagine::PURPLE,  \
                    Imagine::BLACK,     \
                    Imagine::YELLOW   \
                    } // color pack for clusters display (9 colors)

// adjust these parameters for testing
#define N_MODELS      1
#define N_INLIERS     40 // for a model
#define N_OUTLIERS    10 // in general data set

#define MAX_NOISE     0.01 // max value added to an inlier to ennoise the model (default : 0.01)


#define N_COLORS 9

#endif // SETTINGS_H
