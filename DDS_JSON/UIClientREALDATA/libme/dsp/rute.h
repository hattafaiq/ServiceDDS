/*
	header rute
	furkan jadid
	6 mei 2009
	daun biru engineering
	
	*/
#ifndef RUTE_H
#define RUTE_H

#define ID_DUMP_RPM		9196
#define ID_DUMP_BUANG	9194

#define	BLM_TRAP			0x5555
#define	SUDAH_TRAP        	0xAAAA  	// -> 10101010101 16 bit
//#define FLAG_OFF_RUTE		0x55AA

#define 	OFFSET_RUTE		(64 + 4)

#define BESAR_PAKET  	400

#ifdef __cplusplus
extern "C" {
#endif

struct t_rute {
	unsigned short 	flag;				 	// 2 sudah di trap atau belum
	unsigned short	point_ke;         		// 2 baru ditambahkan
	char 			jeneng[10];     	  	//10
	short  			sudut_fasa;     	  	//2
	unsigned char	kanal;					// 20 Jan 2011, sofhaliza sudah sejak 11 Okt 2010
	unsigned char 	mask;					// 20 jan 2011
	short			tipe_data;    	    	//2
	unsigned short	id_titik;         		//2     
	unsigned short	id_mesin;				//2	total = 38 bytes	--> id_rute
	unsigned short 	id_dikirim;				//2	ditambahkan 17 juli, supaya satu rute bisa dipakai beberapa kali
};


struct t_kom_dat {                          //struk paket komunikasi
    char            kpl[10];
    char            iden[6];
    struct t_rute   rute;
	unsigned short 	data[ BESAR_PAKET ];
	unsigned short	cek[10];
};

typedef struct {
  	unsigned short pjg[31];		//31 * 2 = 62 bytes		--> bisa dipakai sebagai 15 float
  	unsigned short rpm_w[31];		//31 * 2 = 62 bytes	
} pjg_siklus;

/*
struct rute_total {
	data_rute rute_head;
	pjg_siklus p_sik;
};							//total 164 siklus
*/
struct t_info_rotat {
	float 	peak;				// tertinggi pada domain frekuensi
	float	overall;			// harga overall pada domain waktu (sesuai dengan RMS, PP atau P)
	float	f_maks;				// frekuensi saat peak.
    unsigned short keluaran;    // 1=accel, 2=velo, 3=displacement, 4=volt
	unsigned short fft_point;
	unsigned short low_cut;
	unsigned short high_pass;
	unsigned short averages;
	unsigned short window;	
	unsigned short	PP;
	
	/* 16 sept 2009, model integrasi 
		1 untuk digital integration
		2 untuk analog integration (IIR filter)
	*/
	unsigned short integrasi;
	
	/* 19 Sept 2009, skala auto / tidak */
	unsigned short skala;
	
	/* 20 sept 2009, faktor kalibrasi */
	float accel_A;
	float accel_B;
	
	/* 29 Okt 2009 */
	unsigned short satuan;		// metrik, inggris
	unsigned short sat_frek;	// Hz, CPM, RPM
	unsigned short skala_log;	// log, linear
	unsigned short cursor;		// satu saja atau harmonik
	unsigned short screen;		// spektrum saja, + waveform
	
	/* 31 Okt 2009 */
	float f_perlines;			// f_perlines sesungguhnya dari sampling rate sesungguhnya
	
	/* 2 Nov 2009 */
	short cur_avg;
	float faktor_default;		// faktor hanning, hamming dll
	float reff_rpm;
	
	/* 4 Nov 2009 */
	float mean;
	float mean_asli;			// raw data sebelum dikali faktor kalibrasi
	float f_scaling;			// pengaruh scalling
	
	/* 22 Mar 2010 */
	int anal_gain;				// setting analog gain pada LTC1564

	/* 21 Juli 2010 */
	float f_MA;					// milivolt maksimum 
	float f_MI;

	/* 10 Agt 2010 */
	unsigned long 	tim;	/* waktu saat data disimpan */
	unsigned char phase;		// 2 = disable, 1 = enable
	unsigned char kanal;		//  0/1 => 1 kanal, 2 = 2 kanal.

    /* 20 MEI 2013 WARN WARN, mungkin tidak cocok dengan database/sofHaliza */
    int custom_srate;           // sampling rate custom
    int overlap;                // maksimum 100 (100 persen overlap)
};

struct t_info_recip {
        unsigned int    tak_tak;   // 2 / 4 stroke (karakter '2' atau '4')
        unsigned int    ex_buka;
        unsigned int    ex_tutup;
        unsigned int    in_buka;
        unsigned int    in_tutup;
        float           dia_piston;
        float           l_langkah;
        float           l_rod;
		
		/* 25 Mar 2010 */
		int anal_gain;			// setting analog gain pada LTC1564
		float MCA;
		int   MPU_palsu;		// jika 0, maka pakai pickup, jika 1, maka palsu
		float dia_rod;
		float dia_rod_head;		// jika tandem
		
		/* param dsp */
		char enable;			// pressure filter
		char mirror;
		char skala;
		unsigned int stop_P;			/* low cut off */
		unsigned int stop_V;			/* vibrasinya */
		unsigned int start_P;
		unsigned int start_V;

		/* 28 Juli 2010 */
		char dsp;						/* DSP Vibrasi */
		char satuan;					/* G, atau Volt */
		char sample;					/* jumlah sample disimpan, 10, 20, 30, 40 atau 50 */
		int s_rate;
		int p_filter;					/* filter pressure, 0 (disable, 1000, 2000, 3000, 4000, 5000) */

		/* 30 Juli 2010 */
		unsigned long 	tim;	/* waktu saat data disimpan */
} ;

#ifdef __cplusplus
}
#endif

#endif
