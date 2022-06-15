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

    5 Sept 2012
    buat_sinus diganti parameter fungsinya

    float *sin = buat_sinus(int frek, int sampling_rate);
    dibuat fix untuk 1 detik

    18 Nov 2012
    diperluas untuk keperluan generate sinus untuk simulator

    30 Agt 2014
    generate sinus diambil dari :
    http://www.nyu.edu/projects/farbood/2618/src/unit6.2/sine/sine.c
*/

#include <math.h>
#include <float.h>
#include <string.h>
#include <QDebug>
//#include "lain.h"


#if 1
/*  akan membuat sinus sepanjang s_rate

    s_rate : sampling rate
    frek : frekuensi dalam Hz
    amplitudo :
    fasa : sudut fasa geser yang diharapkan dalam derajat
    sinout : input-output yang diharapkan
             ingat, input akan dijumlah dengan output
*/
int buat_sinus( int s_rate, float frek, float amplitudo, float fasa, float *sinout, int tipe_sinyal, int pjg)
{
    int i;
    int period;

    period = (int) ( (s_rate * 1.0)/ frek );

    // hitung rasio fasa (offset) terhadap jumlah data dalam satu periode
    // fasa dalam derajat.
    int offset;
    offset = (int) ((fasa/360.00) * period);

    if (offset < 0) offset = 0;

    if (fasa == 0) offset = 0;

    qDebug("%s():", __FUNCTION__);
    qDebug("s_rate %d, frek %f, amp %f, fasa %f, period %d, ofs %d\n", \
        s_rate, frek, amplitudo, fasa, period, offset);

    double t;
    double d_frek = frek;
    double d_amplitudo = amplitudo;
    double d_offset = offset;
    float temp_kotak;

    qDebug() << tipe_sinyal;

     /* Generate table with sine values at given frequency */
    //for (i = 0; i < s_rate; i++)
    for (i = 0; i < pjg; i++)
    {
        t = ((double) i + d_offset)/(double)s_rate;
        t *= -1.0;  /* menyesuaikan dengan data yang terbalik */

        if (tipe_sinyal == 1){
            //qDebug() << "sinyal segitiga" << tipe_sinyal;
            sinout[i] += (float) fabs(t*d_frek - floor( t*d_frek + 0.5));   // triangle
        }
        else if (tipe_sinyal == 2)  // kotak
        {
            //qDebug() << "sinyal kotak" << tipe_sinyal;
            temp_kotak = (float) (sin(2.00 * M_PI * d_frek * t));
            if (temp_kotak > 0)
                sinout[i] += amplitudo;
            else
                sinout[i] += -1.0 * amplitudo;
        }
        else if (tipe_sinyal == 3){
            //qDebug() << "sinyal gigi gergaji" << tipe_sinyal;
            sinout[i] += (float) (t*d_frek - floor( t*d_frek + 0.5));               // sawtooth
        }
        else{
            //qDebug() << "sinyal sinusoidals" << tipe_sinyal;
            sinout[i] += (float) (d_amplitudo * sin(2.00 * M_PI * d_frek * t));     // sinus
        }

    }

    return period;
}
#endif

#if 0
float gen_sinus(int t, int period, float amplitudo)
{
    float rad = (float) (t * 2 * 3.14 / period);
    //float hasil = (float) (((sin(rad)/2) + 0.5) * 1.0);			// range nya 0 - 1.0
    //float hasil = (float) (sin(rad) * 1.0);			// range nya -1.0 -> 1.0

    float hasil = (float) (sin(rad) * amplitudo);			// range nya -amplitudo -> amplitudo

    return (float) hasil;
}
jjj

/* akan membuat sinyal selama 1 detik (s_rate) */
int buat_sinus( int s_rate, float frek, float amplitudo, float fasa, float *sinout)
{
    int i;
    int period;

    /*
    if (frek == 0)
    {
        period = 1000;

        for (i=0; i<period; i++)	// tes DC
            sinout[i] = 1.00;

        return period;
    }*/

    period = (int) ( (s_rate * 1.0)/ frek );

    // hitung rasio fasa (offset) terhadap jumlah data dalam satu periode
    // fasa dalam derajat.
    int offset;
    offset = (int) ((fasa/360.00) * period);

    if (offset < 0) offset = 0;

    qDebug("%s():", __FUNCTION__);
    qDebug("s_rate %d, frek %f, amp %f, fasa %f, period %d, ofs %d\n", \
        s_rate, frek, amplitudo, fasa, period, offset);

    for (i=0; i<s_rate; i++)
    {
        /* kemungkinan ditambahkan dengan sinus sebelumnya */
        sinout[i] += (float) gen_sinus(i+offset, period, amplitudo);

        //if (i < 10)
        //	printf("%f\n", sinout[i]);
    }

    return period;
}
#endif

