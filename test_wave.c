#include "wave_buffer.h"
#include <math.h>
 
int Round(float myfloat){
  double integral;
  float fraction = (float)modf(myfloat, &integral);
 
  if (fraction >= 0.5)
    integral += 1;
  if (fraction <= -0.5)
    integral -= 1;
 
  return (int)integral;
}


int main(){
	wave test;
	wave_buffer test_buffer;
	int samples = 2000000,i;
	
	
	init_buffer(&test_buffer,mono,44100,16,samples);
	printf("%d",test_buffer.sample_rate);
	alloc_buffer(&test_buffer);
	
	for (i = 0; i < samples;i++){
		test_buffer.buffer[i] = Round(sinf((float) i / 30.0) * 30000);	
	}
	
	buffer_make_chunk(&test_buffer,&test);
	wave_open_file("test.wav","wb",&test);
	wave_write_chunk(&test);
	store_buffer(&test_buffer,&test,0);
	wave_finalize(&test);
	wave_close_file(&test);
	free_buffer(&test_buffer);
}

