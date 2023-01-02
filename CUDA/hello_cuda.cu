#include <stdio.h>

__global__ void helloFromGPU(void)
{
	printf("Hello World From GPU!\n");
}

int main(void)
{
	printf("Hello World from CPU!\n");
	helloFromGPU<<<5,5>>>();
	cudaDeviceReset();

	return 0;
}
