#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#undef min
#undef max

#include "lmcurve.h"

#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
#define SQR(x)          ((x) * (x))

unsigned long long FREQ = 1;

unsigned long long get_time()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return (1000000 * count.QuadPart / FREQ);
}

double f_gaussian(double x, const double *p)
{
    return p[0] * exp(-SQR((x - p[1]) / p[2]));
}

double f_gaussian2(double x, const double *p)
{
    return p[0] * exp(-SQR((x - p[1]) / p[2])) + p[3] * exp(-SQR((x - p[4]) / p[5]));
}

int main(void)
{
    //double par[3] = { 1.0, 100.0, -20.0 };    /* optimized starting value, extracted from MATLAB curve fitting tool */
    double par[6] = { 100.0, 1800.0, 289, -50.0, 1650.0, 215.0 };
    const int N = ARRAY_SIZE(par);     /* number of parameters in model function f */

    /* data points: gaussian with noise */
    double x[] = {
//#include "gaussian_x.h"
#include "zstack_x.h"
    };
    double y[] = {
//#include "gaussian_y.h"
#include "zstack_y.h"
    };
    const int M = ARRAY_SIZE(x);
    int i;
    unsigned long long start, end;

    lm_control_struct control = lm_control_double;
    lm_status_struct status;

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    FREQ = frequency.QuadPart;

    assert(M == ARRAY_SIZE(y));

    printf("Fitting ...\n");
    /* now the call to lmfit */
    start = get_time();
    //lmcurve(N, par, M, x, y, f_gaussian, &control, &status);
    lmcurve(N, par, M, x, y, f_gaussian2, &control, &status);
    end = get_time();

    printf("Fitting took %llu usec\n", end - start);

    printf("Results:\n");
    printf("status after %d function evaluations:\n  %s\n", status.nfev, lm_infmsg[status.outcome]);

    printf("obtained parameters:\n");
    for (i = 0; i < N; ++i)
        printf("  par[%i] = %12g\n", i, par[i]);
    printf("obtained norm:\n  %12g\n", status.fnorm);

    /*
    printf("fitting data as follows:\n");
    for (i = 0; i < M; ++i)
        printf("  x[%2d]=%4g y=%6g fit=%10g residue=%12g\n",
                i, x[i], y[i], f(x[i], par), y[i] - f(x[i], par));
    */

    return 0;
}
