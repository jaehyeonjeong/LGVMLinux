#include <cuda.h>
#include <cuda_run1me_api.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
 cudaDeviceProp prop;
 int count;
 cudaGetDeviceCount(&count);
 for (int i=0; i< count; i++) {
 cudaGetDeviceProper1es(&prop, i);
 prinG(" --- General Informa1on for device %d ---\n", i);
 prinG("Name: %s\n", prop.name);
 prinG("Compute capability: %d.%d\n", prop.major, prop.minor);
 prinG("Clock rate: %d\n", prop.clockRate);
 prinG("Device copy overlap: ");
 prinG(prop.deviceOverlap?"Enabled\n":"Disabled\n");
 prinG("Kernel execu1on 1meout : " );
 prinG(prop.kernelExecTimeoutEnabled?"Enabled\n":"Disabled\n");
 prinG("\n" );
 prinG(" --- Memory Informa1on for device %d ---\n", i);
 prinG("Total global mem: %ld\n", prop.totalGlobalMem);
 prinG("Total constant Mem: %ld\n", prop.totalConstMem);
 prinG("Max mem pitch: %ld\n", prop.memPitch);
 prinG("Texture Alignment: %ld\n", prop.textureAlignment);
 prinG("\n");
 prinG(" --- MP Informa1on for device %d ---\n", i);
 prinG("Mul1processor count: %d\n", prop.mul1ProcessorCount);
 prinG("Shared mem per mp: %ld\n", prop.sharedMemPerBlock);
 prinG("Registers per mp: %d\n", prop.regsPerBlock);
 prinG("Threads in warp: %d\n", prop.warpSize);
 prinG("Max threads per block: %d\n", prop.maxThreadsPerBlock);
 prinG("Max thread dimensions: (%d, %d, %d)\n", prop.maxThreadsDim[0], 
 prop.maxThreadsDim[1], prop.maxThreadsDim[2]
);
 prinG("Max grid dimensions: (%d, %d, %d)\n", prop.maxGridSize[0], 
 prop.maxGridSize[1], prop.maxGridSize[2]);
 prinG("\n");
 }
 return 0;
}