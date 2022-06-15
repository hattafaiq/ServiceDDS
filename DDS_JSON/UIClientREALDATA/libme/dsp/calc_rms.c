/*
	hitung rms
	untuk testing saja

	15 mar 2013
	furkan jadid
	daun biru engineering
*/


#include <math.h>
#include <float.h>

double calc_rms(double *in, int n)
{
	int i;
    double sum = 0;
	
	for (i=0; i<n; i++)
	{
        sum += (double) (in[i] * in[i]);
	}

    return (double) sqrt((sum/n));
}

/* atau digital overall, menurut Parseval's Theorem */
/* lihat buku tebal 1, hal 2-34 */
double digital_rms(double *in, int n)
{
    int i;
    double sum = 0;
    double N = (double)( n * 1.0 );

    for (i=0; i<n; i++)
    {
        sum += (double) (in[i] * in[i]);

        //double d = (double) fabs(in[i]/N);
        //sum += (d * d);

    }
    //return sum;
    return (double) (0.8165 * sqrt(sum));
}
