/**
 * Author        : Lysandre M. (lysandre.macke@enpc.fr)
 * Created       : 04-28-2023
 * Last modified : 05-09-2023
 *
 * Global parameters for J-Linkage algorithm. */

#ifndef SETTINGS_H
#define SETTINGS_H

#define EPSILON       0.1   // threshold for consensus set computing
#define Z             1      // normalization constant
#define SQUARED_SIGMA 2      // for random sampling
#define COLOR_PACK {Imagine::RED,   \
                    Imagine::GREEN,    \
                    Imagine::CYAN,    \
                    Imagine::BLUE,   \
                    Imagine::MAGENTA, \
                    Imagine::ORANGE,  \
                    Imagine::PURPLE,  \
                    Imagine::BLACK,     \
                    Imagine::YELLOW   \
                    } // color pack for clusters display

#define N_INLIERS     40
#define N_OUTLIERS    20

#define N_COLORS 9

#endif // SETTINGS_H
