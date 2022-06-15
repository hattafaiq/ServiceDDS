/*
 *  window filter
 *  furkan jadid
 *  24 April 2013
 *
 *  dipindah dari versi Haliza 9
 */

/*
 *  9 Sept 2009
 * 	buat window sebelum dipakai untuk fft
*/

#include <math.h>
#include "window_filter.h"


void skala_window(double *out, int M, double faktor)
{
    double skala;
    skala = (double) M/2;
    skala = skala * faktor;

    int i;

    /* tadinya belum = M */
    for (i=0; i<=M; i++)
        out[i] = (double) (out[i]/skala);

}



int buat_bandpass(double *filter_kernel, int M, double fc_L, double fc_H, unsigned short kind)
{
    /*	lihat buku DSP Guide bab 16 hal 294
        fc adalah cut off, antara 0 sampai 0.5
        M panjang filter

        20 desember 2006, supaya kompatible dengan 5P, kind :
        1. hanning
        2. rectangular
        3. blackman
        4. hamming

        fc_L adalah low pass cut off (Stop frekuensi of interest)
        fcH adalah high pass cut off (start frekeunsi of interest)

        fc harus > fcH
        */

    int i;
    double sum;
    int Mper2;
    double *filter_kernel2;

    filter_kernel2 = malloc( 2 * M *sizeof (double));

    if (filter_kernel2 == 0)
    {
        printf("%s(): Malloc filter_kernel2 error\n", __FUNCTION__);
        return -1;
    }

    printf("%s(): jum %d, fc_L %f, fc_H %f, kind %d\r\n", __FUNCTION__, M, fc_L, fc_H, kind);

    Mper2 = M/2;

    for (i=0; i<(M+1); i++)
    {
        filter_kernel[i] = 0.00;
        filter_kernel2[i] = 0.00;
    }
    //* buat filter kernel LOW PASS
    if (kind == 1)		//hanning
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (double) 2*M_PI*fc_L;
            }
            else
            {
                filter_kernel[i] = (double)sin(2*M_PI*fc_L*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 2)		//rectangular
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (double) 2*M_PI*fc_L;
            }
            else
            {
                filter_kernel[i] = (double)sin(2*M_PI*fc_L*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 3)		//blackman
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (double) 2*M_PI*fc_L;
            }
            else
            {
                filter_kernel[i] = (double)sin(2*M_PI*fc_L*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
        }
    }
    else if (kind == 4)	//hamming
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel[i] = (double) 2*M_PI*fc_L;
            }
            else
            {
                filter_kernel[i] = (double)sin(2*M_PI*fc_L*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.54-0.46*cos(2 * M_PI * i /M));
        }
    }

    sum = 0;
    // normalisasi kernel
    for (i=0; i<M+1; i++)
    {
      sum = sum + filter_kernel[i];
    }

    for (i=0; i<M+1; i++)
    {
        filter_kernel[i]=filter_kernel[i]/sum;
    }

    /* hitung low-pass filter yang kedua sebalum diubah menjadi high pass */

    if (kind == 1)		//hanning
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (double) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (double)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 2)		//rectangular
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (double) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (double)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel[i]=filter_kernel[i]*(0.5-0.5*cos(2 * M_PI * i /M));
        }
    }
    else if (kind == 3)		//blackman
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (double) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (double)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.42-0.5*cos(2 * M_PI * i /M) + 0.08 * cos (4 * M_PI * i /M));
        }
    }
    else if (kind == 4)	//hamming
    {
        for (i=0; i<M+1; i++)
        {
            if ((i-Mper2) == 0)
            {
                filter_kernel2[i] = (double) 2*M_PI*fc_H;
            }
            else
            {
                filter_kernel2[i] = (double)sin(2*M_PI*fc_H*(i-Mper2))/(i-Mper2);
            }
            filter_kernel2[i]=filter_kernel2[i]*(0.54-0.46*cos(2 * M_PI * i /M));
        }
    }

    sum = 0;
    // normalisasi kernel
    for (i=0; i<M+1; i++)
    {
      sum = sum + filter_kernel2[i];
    }

    for (i=0; i<M+1; i++)
    {
      filter_kernel2[i]=filter_kernel2[i]/sum;
    }
    //selesai menyiapkan high pass


   /* mengubah kernel yang kedua menjadi high pass sebagaimana pada gambar 14.5
      dan program 16.2 halaman 295 */
   for (i=0; i<M+1; i++)
   {
      filter_kernel2[i] = -1 * filter_kernel2[i];
   }
   filter_kernel2[Mper2] = filter_kernel2[Mper2] + 1;

   /* untuk mendapatkan band reject, tambahkan filter 1 dan filter 2*/
   for (i=0; i<M+1; i++)
   {
      //H_kernel[i] = filt_kernel1[i] + filt_kernel2[i];
      filter_kernel[i] = filter_kernel[i] + filter_kernel2[i];
   }

   /* untuk mendapatkan band pass, maka diubah */
   for (i=0; i<M+1; i++)
   {
      filter_kernel[i] = -1 * filter_kernel[i];
   }
   filter_kernel[Mper2] = filter_kernel[Mper2] + 1;

   free( filter_kernel2 );

   return 0;

   /* konvolusi
   for (i=M ; i<(jum+M); i++)
   {
      out[i] = 0;
      for (k=0; k<M+1; k++)
      {
         out[i] = out[i] + ini[i-k]*H_kernel[k];
      }
   }*/

}
