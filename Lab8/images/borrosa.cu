#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include "lodepng.h"
#include "lodepng.cu"

__global__
void borrosa(unsigned char* d_Pin, unsigned char* d_Pout, int n, int m){
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  
  int pixValR = 0, pixValG = 0, pixValB = 0;
  //BLUR_SIZE = nivel de intensidad
  int BLUR_SIZE = 20, blurRow, blurCol;

  if(x < n*m) {
    int pixels=0;
    for(blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE+1;++blurRow){
    	for(blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE+1;++blurCol){
	    int curX = blurCol + x;
	    int new_x = (blurRow*m + curX)*4;
	    if(curX > -1 && curX < n*m*4 && new_x > -1 && new_x < n*m*4){
	      pixValR += d_Pin[new_x];
	      pixValG += d_Pin[new_x+1];
	      pixValB += d_Pin[new_x+2];
	      pixels++;
	    }
	}

	d_Pout[x*4] = (unsigned char)(pixValR/pixels);
    	d_Pout[x*4+1] = (unsigned char)(pixValG/pixels);
    	d_Pout[x*4+2] = (unsigned char)(pixValB/pixels);
    	d_Pout[x*4+3] = d_Pin[x*4+3];
    }
  }
}

void dibujar(unsigned char* Pin, unsigned char* Pout, int n, int m){
  unsigned char* d_Pout, *d_Pin;
  long int size = n*m*4;
  cudaMalloc((void **) &d_Pin,size);
  cudaMemcpy(d_Pin, Pin, size, cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_Pout,size);

  borrosa<<<(size-1)/256+1,256>>>(d_Pin,d_Pout,n,m);

  cudaMemcpy(Pout, d_Pout, size, cudaMemcpyDeviceToHost);
  cudaFree(d_Pin); cudaFree(d_Pout);
}

int main(){
  unsigned char *image, *out_image;
  int i;
  char name_in[100], name_out[100];
  unsigned width, height;
//ejemplo :
 /* name_in="Tokomon2.png";
  name_out="tokoBorrosa.png";*/
  scanf("%s %s", name_in, name_out);
  i = lodepng_decode32_file(&image, &width, &height, name_in);

  if(i < 0) printf("NO\n");
  out_image = (unsigned char*) malloc(width*height*4);

  dibujar(image,out_image,height,width);
  //dibujar out_imagen
  lodepng_encode32_file(name_out,out_image,width,height);

  free(image);
  free(out_image);
  return 0;
}
