#ifndef UTILS_H
#define UTILS_H


#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    double maks;
    double min;
    double x_maks;
    double x_min;
    int i_maks;
    int i_min;
} t_marker;


double get_maks(double *in, int len);
double get_min(double *in, int len);
int get_marker(double *in, double *in_x, int len, t_marker *tm);

int buat_sinus(double frek, double *sinout, double range, int def_sampling_rate, double dc);

#ifdef __cplusplus
}
#endif


#endif // UTILS_H
