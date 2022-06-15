/*
	22 agt 2009
	furkan jadid
	bekasi, daun biru engineering
	
	fungsi untuk generate sinus 
	dicopy dari sig_gen yang dipakai untuk lipi
	
	menghasilkan short 0 - 0xFFFF
	
	30 agt 2009
	test untuk desain filter
    diganti ke float hasilnya
	
	1 Sept 2009
	buat_sinus diumpan array dari luar 
	
    25 April 2013
    Dicopy ke versi QT
    Format double precission

    header ada di utils.h

*/

//#include "FreeRTOS.h"
#include <math.h>
//#define def_sampling_rate	25600

#define konstan (9800.00 * 2500.00 * 0.01)

#define USE_DUMMY_SINUS 1


#if (USE_DUMMY_SINUS == 1)

static double gen_sinus(int t, int period, double range)
{
    double rad = (double) (t * 2 * 3.14 / period);
	//float hasil = (float) (((sin(rad)/2) + 0.5) * 1.0);			// range nya 0 - 1.0
	
	//float hasil = (float) (sin(rad) * 1.0);			// range nya -1.0 -> 1.0
    double hasil = (double) (sin(rad) * range);			// range nya -0.2 -> 0.2
	
	//float hasil = (float) (((sin(rad)/2.00) + 0.5) * 65535.00);			// range nya 0 - 65.000 k
	
	//float hasil = (float) (sin(rad) * 1.0 * 65535.00);			// range nya -1.0 -> 1.0
	
    return (double) hasil;
}

/* return adalah periode yang mungkin */
int buat_sinus(double frek, double *sinout, double range, int def_sampling_rate, double dc)
{
	int i;
	int y;
	int period;
	int per_period;		/* per sepuluhnya */
	int per_period3; 	/* per delapannya */
    double range2;	/* range yang lebih kecil */
    double range3;
	
	if (frek == 0)
	{
		period = 1000;
		
		for (i=0; i<period; i++)	// tes DC
			sinout[i] = 1.00;
		
		return period;
	}
	
	period = (int) ( def_sampling_rate * 1.0 / frek );
    per_period = (int) (period / 11);
	//per_period = (int) (period / 2);
	per_period3 = (int) (period / 8);
    range2 = (double) (range/4);
	//range2 = (float) range;
    range3 = (double) (range/100.00);
		
    for (i=0; i<period; i++)
    {
        sinout[i] = (double) gen_sinus(i, period, range);
        sinout[i] += (double) gen_sinus(i, per_period, range2);
        //sinout[i] += (double) gen_sinus(i, per_period3, range3);

        sinout[i] += dc;
	}
	
	printf("%s(): frek = %f, period = %d, per_per %d, range2 = %f\r\n", __FUNCTION__, frek, period, per_period, range2);
	
	return period;
}

#endif
