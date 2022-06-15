/*
 * furkan jadid
 * daun biru engineering
 *
 * 24 April 2013
 * fungsi2 umum
 */

#include "utils.h"

double get_maks(double *in, int len)
{
    double temp = -1000000.00;
    int i;

    for (i = 0; i<len; i++)
    {
        if ( in[i] > temp) temp = in[i];
    }

    return temp;
}

double get_min(double *in, int len)
{
    double temp = 1000000.00;
    int i;

    for (i = 0; i<len; i++)
    {
        if ( in[i] < temp) temp = in[i];
    }

    return temp;
}

/* in adalah sumbu y, in_x untuk sumbu x */
int get_marker(double *in, double *in_x, int len, t_marker *tm)
{
    int i;
    tm->maks = -4000000000.00;
    tm->min = 4000000000.00;

    for (i=0; i<len; i++)
    {
        if (in[i] > tm->maks)
        {
            tm->maks = in[i];
            tm->x_maks = in_x[i];
            tm->i_maks = i;
        }
        if (in[i] < tm->min)
        {
            tm->min = in[i];
            tm->x_min = in_x[i];
            tm->i_min = i;
        }
    }

    return 0;
}

