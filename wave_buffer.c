#include "wave_buffer.h"
#include <stdarg.h>

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
/*mix two or more buffers, the paramter start specifies were the buffers will start to be mixed in the first buffer*/
void mix_wave_buffers(wave_buffer * wav1,wave_buffer ** mix,int start){
	int i,j,sample;
	long int max_size = 0;
	wave_buffer ** tmp = mix;
	
	if (wav1 == NULL || tmp == NULL || *tmp == NULL)
		return;
		
	if (start >= wav1->size)
		return;
		
	max_size = (*tmp++)->size;
	for (; *tmp != NULL;tmp++){
		if ((*tmp)->size > max_size)
			max_size = (*tmp)->size;			
	}
	
	for (i = 0; i < max_size,(i+start) < wav1->size;i++){
		for (tmp = mix,j = 0,sample = wav1->buffer[i+start]; *tmp != NULL;tmp++,j++)	{
			if (i < (*tmp)->size)
				sample += (*tmp)->buffer[i+start];				
		}
		wav1->buffer[i+start] = sample / (j+1);			
	}
		
}

