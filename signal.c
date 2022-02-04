#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/**
 * @brief square signal generator
 * 
 * @param x input
 * @param resolution number of fourier serie's members
 * @return double output
 */
double square(double x, unsigned resolution);

/**
 * @brief triangle signal generator
 * 
 * @param x input
 * @param resolution number of fourier serie's members
 * @return double output
 */
double triangle(double x, unsigned resolution);

/**
 * @brief saw signal generator
 * 
 * @param x input
 * @param resolution number of fourier serie's members
 * @return double output
 */
double saw(double x, unsigned resolution);

/**
 * @brief square signal generator
 * 
 * @param x input
 * @param resolution nothing
 * @return double output
 */
double sinus(double x, unsigned resolution);

/**
 * @brief print help text
 * 
 */
void print_help(void);


int main(int argc, char const *argv[])
{
    
    enum {SQUARE, TRIANGLE, SAW, SIN};
    const int default_signal = SQUARE;
    int signal = default_signal;

    const int default_resolution = 20;
    int resolution = default_resolution;

    const double default_amplitude = 20;
    double amplitude = default_amplitude;

    const int default_length = 10000;
    int length = default_length;

    const double default_time = 0.1; // s
    double time = default_time;

    const double default_scale = 0.001;
    double scale = default_scale;

    const double default_e = 0;
    double e = default_e;

    // resolve arguments
    for (int i = 1; i < argc;++i) {
        // print help
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return 1;
        }

        // signal option
        // t - type
        if (strcmp(argv[i], "-t") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-t needs additional option\n");
                return -1;
            }

            // set signal
            if (strcmp(argv[i + 1], "square") == 0) {
                signal = SQUARE;
            } else if (strcmp(argv[i + 1], "triangle") == 0) {
                signal = TRIANGLE;
            } else if (strcmp(argv[i + 1], "saw") == 0) {
                signal = SAW;
            } else if (strcmp(argv[i + 1], "sin") == 0) {
                signal = SIN;
            } else {
                fprintf(stderr, "signal %s is not implemented\n", argv[i + 1]);
                return -1;
            }

            ++i;
        }

        // r - comp. resolution
        if (strcmp(argv[i], "-r") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-r needs additional numeric option\n");
                return -1;
            } 

            resolution = atoi(argv[i + 1]);
            ++i;
        }

        // l - length
        if (strcmp(argv[i], "-l") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-l needs additional numeric option\n");
                return -1;
            } 

            length = atoi(argv[i + 1]);
            ++i;
        }

        // T - time
        if (strcmp(argv[i], "-T") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-T needs additional numeric option\n");
                return -1;
            } 

            time = atof(argv[i + 1]);
            ++i;
        }


        // s - scale
        if (strcmp(argv[i], "-s") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-s needs additional numeric option\n");
                return -1;
            } 

            scale = atof(argv[i + 1]);
            ++i;
        }

        // a - amplitude
        if (strcmp(argv[i], "-a") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-a needs additional numeric option\n");
                return -1;
            } 

            amplitude = atof(argv[i + 1]);
            ++i;
        }

        // e - x exp
        if (strcmp(argv[i], "-e") == 0) {
            // check for option
            if (i + 1 == argc) {
                fprintf(stderr, "-e needs additional numeric option\n");
                return -1;
            } 

            e = atof(argv[i + 1]);
            ++i;
        }

    }   

    double(*func)(double, unsigned);

    switch (signal) {
    case SQUARE:
        func = square;
        break;

    case TRIANGLE:
        func = triangle;
        break;

    case SAW:
        func = saw;
        break;

    case SIN:
        func = sinus;
        break;
    
    default:
        break;
    }

    time_t t0, t1;
    for (int i = 0; i < length; i++) {
        t0 = clock();
        double y = func(i * (double)scale, resolution);
        if (e != 0) {
            y *= exp(e*i);
        }

        y *= amplitude;

        printf("%lf\n", y);
        fflush(stdout);

        t1 = clock();

        usleep((time - (t1 - t0)/CLOCKS_PER_SEC)*1000000);
    }
    
    return 0;
}


double square(double x, unsigned resolution) {
    double res = 0;

    for (int j = 1; j < resolution; ++j) {
        res += sin((2*j - 1) * x) / (2*j - 1);
    }
    
    return res;
}


double triangle(double x, unsigned resolution) {
    double res = 0;

    for (int j = 1; j < resolution; ++j) {
        res += pow(-1, j) * sin((2*j - 1) * x) / pow((2*j - 1), 2);
    }
    
    return res;
}


double saw(double x, unsigned resolution) {
    double res = 0;

    for (int j = 1; j < resolution; ++j) {
        res += pow(-1, j) * sin(j* x) / j;
    }
    
    return res;
}


double sinus(double x, unsigned resolution) {
    return sin(x);
}


void print_help(void) {
    printf(
        "┌───────────────────────────────────────────────────────────────┐\n"
        "│                 SIGNAL GENERATION PROGRAM                     │\n"
        "├───────────────────────────────────────────────────────────────┤\n"
        "│  Program outputs signal to stdout (double)                    │\n"
        "│                                                               │\n"
        "│  Options:                                                     │\n"
        "│    -h print this help                                         │\n"
        "│    -t [type] change signal type                               │\n"
        "│        square, triangle, saw, sin                             │\n"
        "│    -r [int] fourier series resolution                         │\n"
        "│    -l [int] length of the signal                              │\n"
        "│    -T [double] time between signals [s]                       │\n"
        "│    -s [float] output x scale                                  │\n"
        "│    -a [float] output y scale (amplitude)                      │\n"
        "│    -e [float] multiply output by exp(e)                       │\n"
        "│                                                               │\n"
        "└───────────────────────────────────────────────────────────────┘\n"
    );
}
