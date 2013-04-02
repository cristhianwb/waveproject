#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"
 
void wave_read_chunk(wave * wav){
	if (wav == NULL || wav->f == NULL)
		return;
	fread(&wav->wave_chunk,sizeof(Chunk),1,wav->f);
	wav->data = ftell(wav->f);
}

void wave_write_chunk(wave * wav){
	if (wav == NULL || wav->f == NULL)
		return;
	fwrite(&wav->wave_chunk,sizeof(Chunk),1,wav->f);
	wav->data = ftell(wav->f);
}


short int wave_open_file(char * fname,char * mode,wave * wav){
	wav->f = fopen(fname,mode);
	if (wav->f == NULL)
		return -1;		
	return 0;
} 

void wave_initialize(wave * wav,short int channels,int sample_rate,short int bit_sample){
	Chunk * c;
	const char * format = "WAVE";
	const char * id = "fmt ";
	const char * id2 = "data";
	const char * id3 = "RIFF";	
	
	if (wav == NULL)
		return;
		
	c = &wav->wave_chunk;
	
	memcpy(c->id,id3,4);
	c->size = sizeof(Chunk) - 8;
	memcpy(c->format,format,4);
	memcpy(c->subchunk1.id,id,4);
	c->subchunk1.size = sizeof(c->subchunk1) - 8;
	c->subchunk1.audio_format = 1;
	c->subchunk1.num_channels = channels;
	c->subchunk1.sample_rate = sample_rate;
	c->subchunk1.byte_rate = sample_rate * channels * bit_sample / 8;
	c->subchunk1.block_align = channels * bit_sample / 8;
	c->subchunk1.bits_per_sample = bit_sample;
	memcpy(c->subchunk2.id,id2,4);
	c->subchunk2.size = 0;
	
}

void write_sample(wave * wav,short int s){
	if (wav == NULL || wav->f == NULL)
		return;
	fwrite(&s,sizeof(short int),1,wav->f);
}

short int read_sample(wave * wav){
	if (wav == NULL || wav->f == NULL)
		return;
	short int s;
	fread(&s,sizeof(short int),1,wav->f);
	return s;
}

void wave_finalize(wave * wav){
	if (wav == NULL)
		return;
	wav->wave_chunk.subchunk2.size = ftell(wav->f) - wav->data;
	wav->wave_chunk.size = ftell(wav->f) - 8;
	rewind(wav->f);
	wave_write_chunk(wav);
}


void wave_close_file(wave * wav){
	if (wav == NULL || wav->f == NULL)
		return;
	fclose(wav->f);
}



