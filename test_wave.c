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
	int samples = 2000000,i,j,sounds,f;
	wave_buffer **bufs;
	scanf("%d",&sounds);	
	bufs = (wave_buffer**) malloc( (sounds+1) * sizeof(wave_buffer*));
	for (i = 0;i < sounds;i++){
		bufs[i] = (wave_buffer*) malloc(sizeof(wave_buffer));
		init_buffer(bufs[i],mono,44100,16,samples);
		alloc_buffer(bufs[i]);
		scanf("%d",&f);
			for (j = 0; j < samples;j++)
				bufs[i]->buffer[j] = Round(sinf( (float) j / f) * 30000);	
	}
	
	bufs[i] = NULL;
	
	mix_wave_buffers(*bufs,bufs+1,0);

	buffer_make_chunk(*bufs,&test);
	wave_open_file("test.wav","wb",&test);
	wave_write_chunk(&test);
	store_buffer(*bufs,&test,0);
	wave_finalize(&test);
	wave_close_file(&test);
	
	for (i = 0; i < sounds;i++)
		free_buffer(bufs[i]);
	free(bufs);
	
}

