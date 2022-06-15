#ifndef SETTING_H
#define SETTING_H

//#define SUMBU_FONT  "Helvetica"

#define JUM_MODULE      1//2
#define JUM_PLOT        4//8
#define JUM_KURVA       4//8
#define JUM_KANAL       4
#define JUM_CURVE       8//16

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


struct tt_req2 {
    char head[10];
    unsigned short sps;//KUKU
    char cur_kanal;
    int kanal_enable;       /* jumlah kanal aktif */
    int request_sample;		/* sample diminta */
    unsigned char buf[ BESAR_PAKET ];
};

struct data0{
    //int sender;
    int jumlah_paket;
    float data_kirim;
};

struct data1{
    float data_kirim1[2560];
};


#endif // SETTING_H
