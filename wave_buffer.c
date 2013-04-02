#include "wave_buffer.h"

void init_buffer(wave_buffer * buf,short int channels,int sample_rate,short int bit_sample,long int size){
	if (buf == NULL)
		return;
		
	buf->channels = channels;
	buf->sample_rate = sample_rate;
	buf->bit_sample = bit_sample;
	buf->size = size;
	buf->buffer = NULL;
}

void load_buffer(wave_buffer * buf,wave * wav,long int length){
	int i;
	short int s;
	if (buf == NULL || wav == NULL)
		return;
		
	buf->channels = wav->wave_chunk.subchunk1.num_channels;
	buf->sample_rate = wav->wave_chunk.subchunk1.sample_rate;
	buf->bit_sample = wav->wave_chunk.subchunk1.bits_per_sample;
	
	if (length == 0)
		length = wav->wave_chunk.subchunk2.size;
	
	buf->buffer = (short int*) malloc(length * sizeof(short int));
	
	if (buf->buffer == NULL)
		return;
		
	for (i = 0;i < length;i++){
		if (feof(wav->f))
			break;
		buf->buffer[i] = read_sample(wav);
	}
	
	buf->size = i;	
}

void store_buffer(wave_buffer * buf,wave * wav,long int length){
	int i;
	if (buf == NULL || wav == NULL)
		return;
	if (length == 0)
		length = buf->size;
	
	for (i = 0; i < length;i++)
		write_sample(wav,buf->buffer[i]);	
}
 
/*makes a chunk in a wave file from a wave_buffer*/
void buffer_make_chunk(wave_buffer * buf,wave * wav){
	if (buf == NULL)
		return;
	wave_initialize(wav,buf->channels,buf->sample_rate,buf->bit_sample);
}

/*allocates a buffer*/
void alloc_buffer(wave_buffer * buf){
	if (buf == NULL)
		return;
	buf->buffer = (short int*) calloc(buf->size,sizeof(short int));
}

/*free a buffer*/
void free_buffer(wave_buffer * buf){
	if (buf == NULL)
		return;
	free(buf->buffer);
}

