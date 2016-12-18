//
// Created by salmon on 16-7-20.
//
#include <assert.h>
#include <mpi.h>
#include "spParallel.h"
#include "spMPI.h"


int spParallelInitialize(int argc, char **argv)
{

    spMPIInitialize(argc, argv);

    spParallelDeviceInitialize(argc, argv);

    return SP_SUCCESS;
}

int spParallelFinalize()
{
    spParallelDeviceFinalize();

    spMPIFinalize();

    return SP_SUCCESS;
}

int spParallelGlobalBarrier()
{
    spMPIBarrier();
    return SP_SUCCESS;
};


int spParallelThreadBlockDecompose(size_type num_of_threads_per_block, size_type grid_dim[3], size_type block_dim[3])
{
    block_dim[0] = num_of_threads_per_block;
    block_dim[1] = 1;
    block_dim[2] = 1;

    while (block_dim[0] > grid_dim[0])
    {
        block_dim[0] /= 2;
        block_dim[1] *= 2;
    }

    while (block_dim[1] > grid_dim[1])
    {
        block_dim[1] /= 2;
        block_dim[2] *= 2;
    }
    for (int i = 0; i < 3; ++i)
    {
        size_type L = grid_dim[i];
        grid_dim[i] = L / block_dim[i];
        if (grid_dim[i] * block_dim[i] < L) { ++(grid_dim[i]); }
    }

    return SP_SUCCESS;

}


int spParallelDeviceInitialize(int argc, char **argv) { return SP_DO_NOTHING; }

int spParallelDeviceFinalize() { return SP_DO_NOTHING; }

int spMemoryDeviceAlloc(void **p, size_type s) { return SP_DO_NOTHING; }

int spMemoryDeviceFree(void **p) { return SP_DO_NOTHING; }

int spMemoryHostAlloc(void **p, size_type s) { return SP_DO_NOTHING; }

int spMemoryHostFree(void **p) { return SP_DO_NOTHING; }

int spMemoryCopy(void *dest, void const *src, size_type s) { return SP_DO_NOTHING; }

//int spMemoryCopyToCache(void *dest, void const *src, size_type s) { return SP_DO_NOTHING; }

int spMemorySet(void *p, int v, size_type s) { return SP_DO_NOTHING; }

int spMemoryDeviceToHost(void **p, void *src, size_type size_in_byte) { return SP_DO_NOTHING; }

//int spMemoryHostFree(void **p) { return SP_DO_NOTHING; }

int spParallelDeviceSync() { return SP_DO_NOTHING; }

//int spParallelGlobalBarrier() { return SP_DO_NOTHING; }

int spParallelAssign(size_type num_of_point, size_type *offset, Real *d, Real const *v) { return SP_DO_NOTHING; }

int spParallelDeviceFillInt(int *d, int v, size_type s) { return SP_DO_NOTHING; }

int spParallelDeviceFillReal(Real *d, Real v, size_type s) { return SP_DO_NOTHING; }
//
//int spParallelGridDim();
//
//int spParallelBlockDim();

//int spParallelThreadBlockDecompose(size_type num_of_threads_per_block, size_type grid_dim[3],
//                                   size_type block_dim[3]) { return SP_DO_NOTHING; }
