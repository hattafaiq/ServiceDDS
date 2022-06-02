#ifndef DATASETUP_H
#define DATASETUP_H

#define DEF_JUDUL   "Online Monitoring System"

#define SUMBU_FONT  "Ubuntu"
//#define SUMBU_FONT  "Helvetica"

#define JUM_MODULE      2
#define JUM_PLOT        8
#define JUM_KURVA       8
#define JUM_KANAL       4
#define JUM_CURVE       16

#define JUM_BAND_AREA   5

#define MAX_LEN_DATA    100000  /* 100 k Sample x 8 byte double */
#define LEN_DUMMY       5000
#define SET_CEK         "daunbiru_maumere_01"

#define BESAR_PAKET     1024
#define BESAR_PAKET_F	(BESAR_PAKET / 4)
//KUKU
#define LEN_TEST        2560

#define MAX_FFT_POINT   16540 /* Max line : 6400 --> spektrum_point untuk fft = line * const Nyquist
                                                                               = 6400 * 2.56 = 16284
                                  16284 + 256 (biar ga mepet) */

#define PORT_CILIWUNG_SEND       5006
#define PORT_CILIWUNG_RECV       5007
#define PORT_CILIWUNG_DATA       5008

/* Note */
#define KIND_TRENDING   1
#define KIND_REPLAY     2

/* Alarm */
#define ON              1
#define OFF             0

#define DEFAULT         ":/icon/led_off.png"
#define LOW             ":/icon/led_green.png"
#define MEDIUM          ":/icon/led_yellow.png"
#define HIGH            ":/icon/led_red.png"

/* Database Driver */
#define SQLITE          1
#define MYSQL           2
#define POSTGRESQL      3

#if 1
#define FMAX            5000
#else
#define FMAX            4000
#endif

/* Trending */
#define TREND_RMS        "rms"
#define TREND_OVERALL    "overall"
#define TREND_PEAKMIN    "peakmin"
#define TREND_PEAKMAX    "peakmax"
#define TREND_PEAKTOPEAK "peakmin, peakmax"

#define SEC        "sec"
#define MIN        "min"
#define HOUR       "hour"
#define DAY        "day"
#define MON        "month"

/* Peak Marker Status */
#define SHOW_PEAK  0
#define HIDE_PEAK  1
#define IDLE_PEAK  2

/* Harmonic Marker Status */
#define SHOW_HARMONIC  3
#define HIDE_HARMONIC  4
#define IDLE_HARMONIC  5

#define WAVEFORM    1
#define SPEKTRUM    2

#define OVERALL_DATA    1
#define PEAK_DATA       2
#define PEAK_PEAK_DATA  3

/* plot adalah parent dari kurva */
struct t_plot_setting {
    int  flag_enable;    /* dimunculkan tidak ? */

    char judul[128];
    char judul_bawah[128];

    char judul_sumbu_y[128];
    int  satuan_nilai;

    int  index_judul_sb_y;

    char judul_sumbu_x_wave[128];
    int  index_judul_sb_x_wave;

    char judul_sumbu_x_spek[128];
    int  index_judul_sb_x_spek;

    float resolusi_wave;
    float resolusi_spek;

    int interval_wave;
    int interval_spek;

    int trend_param;    /* Peak Max, Peak Min, RMS, Peak-Peak */
    int kanal_out;      /* Acc, Vel, Disp, Volt */

    char vib_title[32];

    float reff_rpm;
    float alarm_ll;
    float alarm_l;
    float alarm_h;
    float alarm_hh;

    int en_alarm1;
    int en_alarm2;

    char warna[8];

};

struct t_db_setting
{
    int  db_driver;
    char db_ip[32];
    int  db_hari_ditahan;
    int  db_period_simpan;
    char db_nama[64];
    char db_pass[64];
    char db_user[64];
    char db_directory[1024];
    int  db_buffer;
    int  db_port;  /*Jono, 21 Des 2018*/
};

struct t_waveform {
    int len;
    int en_auto_len;
    int en_auto_scale;
    float amp_min;
    float amp_max;

    int en_filter;
    float f_cutoff;
};

struct t_spektrum {
    int line;
    int avg;
    int window;
    int len;
    int en_auto_len;
    int en_auto_scale;
    float amp_min;
    float amp_max;
};

struct t_band_analisis {
    float min_freq[JUM_BAND_AREA];
    float max_freq[JUM_BAND_AREA];
    float alarm_l[JUM_BAND_AREA];
    float alarm_h[JUM_BAND_AREA];
};

struct t_setting
{
    int  fmax;
    char modul1_ip[32];
    char modul2_ip[32];
    int  en_modul_ext1;
    int  protokol_modul;
    int  refresh;
    struct t_db_setting db_setting;
    struct t_plot_setting plot_set[ JUM_PLOT ];
    struct t_waveform wave;
    struct t_spektrum spek;
    struct t_band_analisis band[JUM_KANAL];
    char cek_set[32];
};

struct tt_req2 {
    char head[10];
    unsigned short sps;//KUKU
    char cur_kanal;
    int kanal_enable;       /* jumlah kanal aktif */
    int request_sample;		/* sample diminta */
    unsigned char buf[ BESAR_PAKET ];
};


struct flag_utama{
    int flag_ok;
    int flag_ok_2;
    int flag_ok_3;
};

#endif // DATASETUP_H
