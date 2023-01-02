#include <cuda.h>
#include <cuda_run1me_api.h>
#include <stdio.h>
#include <stdlib.h>
// This func1on wraps the CUDA Driver API into a template func1on
template <class T>
inline void getCudaADribute(T *aDribute, CUdevice_aDribute device_aDribute, 
 int device)
{
 CUresult error = cuDeviceGetADribute(aDribute, device_aDribute, device);
 if(CUDA_SUCCESS != error) {
 fprinP(stderr, "cuSafeCallNoSync( ) Driver API error = %04d from file <%s>, line %i.\n", err
or, __FILE__, __LINE__);
 exit(-1);
 }
}
int main() 
{
 prinP("CUDA Version %i\n", CUDA_VERSION);
 prinP("CUDA Version %s\n", VERSION_STATUS);
 prinP("\nDriver\n");
 cuInit(0);
 int driverVersion, run1meVersion;
 cudaDriverGetVersion(&driverVersion);
 cudaRun1meGetVersion(&run1meVersion);
 prinP(" CUDA Version : %i\n", driverVersion);
 prinP(" Run1me version : %i\n", run1meVersion);
 int deviceCount = 0;
 cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
 prinP(" Number of device : %i\n", deviceCount);
 int value;
 cudaDeviceProp prop;
for(int id = 0; id < deviceCount; id++) {
 cudaGetDeviceProper1es(&prop, id);
 prinP(" Device Name : %s\n", prop.name);
 prinP(" Total global mem : %ld\n", prop.totalGlobalMem);
 prinP(" Total Constant Mem : %ld\n", prop.totalConstMem);
 prinP("\n ADribute(%i)\n", id+1);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK, id);
 prinP(" Max Threads per Block : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X, id);
 prinP(" Max Block DIM(x) : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y, id);
 prinP(" Max Block DIM(y) : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z, id);
 prinP(" Max Block DIM(z) : %i\n", value);
getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY, id);
 prinP(" Total Constant Memory : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_WARP_SIZE, id);
 prinP(" Warp size : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE, id);
 prinP(" Clock Rate : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH, id);
 prinP(" Memory Bus Width : %i\n", value);
 getCudaADribute<int>(&value, CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE, id);
 prinP(" L2 Cache Size : %i\n", value);
 }
 return EXIT_SUCCESS;
}