#include <stdio.h>

#define stereo 2
#define mono 1
 
typedef struct chunk{
	
	char id[4];
	int size;
	char format[4];
	struct {
		char id[4];
		int size;
		short int audio_format;
		short int num_channels;
		int sample_rate;
		int byte_rate;
		short int block_align;
		short int bits_per_sample;	
	}subchunk1;
	
	struct {
		char id[4];
		int size;
	}subchunk2;
	
	
}Chunk;


typedef struct _wave{
	Chunk wave_chunk;
	int samples;
	FILE * f;
	long int data;			
}wave;

void wave_read_chunk(wave * wav);

void wave_write_chunk(wave * wav);

short int wave_open_file(char * fname,char * mode,wave * wav);

void wave_initialize(wave * wav,short int channels,int sample_rate,short int bit_sample);

void write_sample(wave * wav,short int s);

short int read_sample(wave * wav);

void wave_finalize(wave * wav);

void wave_close_file(wave * wav);

