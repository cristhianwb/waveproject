#include "wave.h"
#include <stdlib.h>

typedef struct _wave_buffer{
	short int channels;
	int sample_rate;
	short int bit_sample;
	short int * buffer;
	long int size;
}wave_buffer;
 
/*initializes a buffer structure*/
void init_buffer(wave_buffer * buf,short int channels,int sample_rate,short int bit_sample,long int size);

/*loads a wave file to the buffer. If length is set to zero 
then all the rest of the file will be read.
*/
void load_buffer(wave_buffer * buf,wave * wav,long int length);

/*stores a buffer on a wave file*/
void store_buffer(wave_buffer * buf,wave * wav,long int length);

/*makes a chunk in a wave file from a wave_buffer*/
void buffer_make_chunk(wave_buffer * buf,wave * wav);

/*allocates a buffer*/
void alloc_buffer(wave_buffer * buf);

/*free a buffer*/
void free_buffer(wave_buffer * buf);


