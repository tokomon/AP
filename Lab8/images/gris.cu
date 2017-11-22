#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include "lodepng.h"
#include "lodepng.cu"

__global__
void gris(unsigned char* d_Pin, unsigned char* d_Pout, int n, int m){
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  x = x*4;
  if(x < n*m*4) {
    unsigned char r = d_Pin[x];
    unsigned char g = d_Pin[x+1];
    unsigned char b = d_Pin[x+2];
    d_Pout[x] = 0.21f*r + 0.71f*g + 0.07f*b;
    d_Pout[x+1] = d_Pout[x];
    d_Pout[x+2] = d_Pout[x];
    d_Pout[x+3] = d_Pin[x+3];
  }
}

void dibujar(unsigned char* Pin, unsigned char* Pout, int n, int m){
  unsigned char* d_Pout, *d_Pin;
  long int size = n*m*4;
  cudaMalloc((void **) &d_Pin,size);
  cudaMemcpy(d_Pin, Pin, size, cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_Pout,size);

  gris<<<(size-1)/256+1,256>>>(d_Pin,d_Pout,n,m);
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
