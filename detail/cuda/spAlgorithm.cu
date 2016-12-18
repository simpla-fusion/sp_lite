//
// Created by salmon on 16-9-13.
//
extern "C"
{
#include <assert.h>
#include "../../spAlogorithm.h"
#include "../sp_device.h"
#include "../../spDataType.h"
#include "../../spMisc.h"
}

#include <thrust/device_ptr.h>
#include <thrust/sort.h>
#include <thrust/scan.h>

#include "../../../../../../../usr/local/cuda/include/host_defines.h"
#include "../../../../../../../usr/local/cuda/include/device_launch_parameters.h"


int sort_by_key(size_type const *key_start, size_type const *key_end, size_type *value)
{
    thrust::sort_by_key(thrust::device_ptr<size_type>((size_type *) key_start),
                        thrust::device_ptr<size_type>((size_type *) key_end),
                        thrust::device_ptr<size_type>(value));

    return SP_SUCCESS;
};

__global__
void spMemoryIndirectCopyKernel(Real *dest, Real const *src, size_type num, size_type const *index)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { dest[s] = src[index[s]]; }
};

int spMemoryCopyIndirect(Real *dest, Real const *src, size_type num, size_type const *index)
{

    if (num > 0)
    {
        SP_CALL_DEVICE_KERNEL(spMemoryIndirectCopyKernel, num / NUMBER_OF_THREADS_PER_BLOCK + 1,
                              NUMBER_OF_THREADS_PER_BLOCK, dest, src, num, index);
    }
    return SP_SUCCESS;
}


__global__
void spMemoryInvIndirectCopyKernel(Real *dest, Real const *src, size_type num, size_type const *index)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { dest[index[s]] = src[s]; }
};

int spMemoryCopyInvIndirect(Real *dest, Real const *src, size_type num, size_type const *index)
{
    if (num > 0) { SP_CALL_DEVICE_KERNEL(spMemoryInvIndirectCopyKernel, num / 256 + 1, 256, dest, src, num, index); }
    return SP_SUCCESS;
}

__global__
void spMemoryCopySubArrayRealKernel(Real *dest, Real const *src,
                                    dim3 strides,
                                    dim3 start,
                                    dim3 count)
{
    uint x = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    uint y = __umul24(blockIdx.y, blockDim.y) + threadIdx.y;
    uint z = __umul24(blockIdx.z, blockDim.z) + threadIdx.z;

    if (x < count.x && y < count.y && z < count.z)
    {
        dest[(x * count.y + y) * count.z + z] = src[(start.x + x) * strides.x +
                                                    (start.y + y) * strides.y +
                                                    (start.z + z) * strides.z];


    }

}

__global__
void spMemoryCopySubArraySizeTypeKernel(size_type *dest, size_type const *src,
                                        dim3 strides,
                                        dim3 start,
                                        dim3 count)
{
    uint x = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    uint y = __umul24(blockIdx.y, blockDim.y) + threadIdx.y;
    uint z = __umul24(blockIdx.z, blockDim.z) + threadIdx.z;

    if (x < count.x && y < count.y && z < count.z)
    {
        dest[(x * count.y + y) * count.z + z] = src[(start.x + x) * strides.x +
                                                    (start.y + y) * strides.y +
                                                    (start.z + z) * strides.z];


    }

}

int spMemoryCopySubArray(void *dest, void const *src, int type_tag, size_type const *strides, size_type const *start,
                         size_type const *count)
{
    if (count[0] * count[1] * count[2] == 0) { return SP_SUCCESS; }

    size_type grid_dim[3] = {count[0], count[1], count[2]};

    size_type block_dim[3] = {1, 1, 1};

    SP_CALL(spParallelThreadBlockDecompose(128, grid_dim, block_dim));


    switch (type_tag)
    {
        case SP_TYPE_size_type:
        SP_CALL_DEVICE_KERNEL(spMemoryCopySubArraySizeTypeKernel, sizeType2Dim3(grid_dim), sizeType2Dim3(block_dim),
                              (size_type *) dest, (size_type const *) src, sizeType2Dim3(strides), sizeType2Dim3(start),
                              sizeType2Dim3(count));
            break;


        case SP_TYPE_Real:
        SP_CALL_DEVICE_KERNEL(spMemoryCopySubArrayRealKernel, sizeType2Dim3(grid_dim), sizeType2Dim3(block_dim),
                              (Real *) dest, (Real const *) src, sizeType2Dim3(strides), sizeType2Dim3(start),
                              sizeType2Dim3(count));
            break;

        default:
            UNIMPLEMENTED;
            break;
    }
//    SP_CALL(printArray(dest, type_tag, 3, count));

    return SP_SUCCESS;
}

__global__
void spMemoryCopyInvSubArrayRealKernel(Real *dest, Real const *src, dim3 strides, dim3 start, dim3 count)
{
    uint x = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    uint y = __umul24(blockIdx.y, blockDim.y) + threadIdx.y;
    uint z = __umul24(blockIdx.z, blockDim.z) + threadIdx.z;

    if (x < count.x && y < count.y && z < count.z)
    {
        dest[(start.x + x) * strides.x +
             (start.y + y) * strides.y +
             (start.z + z) * strides.z] = src[(x * count.y + y) * count.z + z];
    }

}

__global__
void spMemoryCopyInvSubArraySizeTypeKernel(size_type *dest, size_type const *src, dim3 strides, dim3 start, dim3 count)
{
    uint x = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    uint y = __umul24(blockIdx.y, blockDim.y) + threadIdx.y;
    uint z = __umul24(blockIdx.z, blockDim.z) + threadIdx.z;

    if (x < count.x && y < count.y && z < count.z)
    {
        dest[(start.x + x) * strides.x +
             (start.y + y) * strides.y +
             (start.z + z) * strides.z] = src[(x * count.y + y) * count.z + z];
    }

}

int spMemoryCopyInvSubArray(void *dest, void const *src, int type_tag, size_type const *strides, size_type const *start,
                            size_type const *count)
{
    if (count[0] * count[1] * count[2] == 0) { return SP_SUCCESS; }
    size_type grid_dim[3] = {count[0], count[1], count[2]};
    size_type block_dim[3];

    SP_CALL(spParallelThreadBlockDecompose(128, grid_dim, block_dim));

    switch (type_tag)
    {


        case SP_TYPE_size_type:
        SP_CALL_DEVICE_KERNEL(spMemoryCopyInvSubArraySizeTypeKernel, sizeType2Dim3(grid_dim), sizeType2Dim3(block_dim),
                              (size_type *) dest, (size_type const *) src, sizeType2Dim3(strides), sizeType2Dim3(start),
                              sizeType2Dim3(count));
            break;


        case SP_TYPE_Real:
        SP_CALL_DEVICE_KERNEL(spMemoryCopyInvSubArrayRealKernel, sizeType2Dim3(grid_dim), sizeType2Dim3(block_dim),
                              (Real *) dest, (Real const *) src, sizeType2Dim3(strides), sizeType2Dim3(start),
                              sizeType2Dim3(count));

            break;

        default:
            UNIMPLEMENTED;
            break;


    }
    return SP_SUCCESS;


}

__global__
void spFillSeqRealKernel(Real *v, size_type num, size_type min, size_type step)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { v[s] = s * step + min; }
};
__global__
void spFillSeqSizeTypeKernel(size_type *v, size_type num, size_type min, size_type step)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { v[s] = s * step + min; }
};

int spFillSeq(void *v, int type_tag, size_type num, size_type min, size_type step)
{
    switch (type_tag)
    {
        case SP_TYPE_Real:
        SP_CALL_DEVICE_KERNEL(spFillSeqRealKernel, num / NUMBER_OF_THREADS_PER_BLOCK + 1, NUMBER_OF_THREADS_PER_BLOCK,
                              (Real *) v, num, min, step);
            break;
        case SP_TYPE_size_type:
        SP_CALL_DEVICE_KERNEL(spFillSeqSizeTypeKernel,
                              num / NUMBER_OF_THREADS_PER_BLOCK + 1, NUMBER_OF_THREADS_PER_BLOCK,
                              (size_type *) v, num, min, step);
            break;
        default:
            UNIMPLEMENTED;
            break;

    }
    return SP_SUCCESS;
};

__global__
void spTransformMinusKernel(size_type *v, size_type const *a, size_type const *b, size_type num)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { v[s] = a[s] - b[s]; }
};

int spTransformMinus(size_type *v, size_type const *a, size_type const *b, size_type num)
{
    /*@formatter:off*/
   spTransformMinusKernel<<<num/256+1,256>>>(v,a,b,num);
    /*@formatter:on*/
    return SP_SUCCESS;

};
__global__
void spTransformAddKernel(size_type *v, size_type const *a, size_type const *b, size_type num)
{
    uint s = __umul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (s < num) { v[s] = a[s] + b[s]; }
};

int spTransformAdd(size_type *v, size_type const *a, size_type const *b, size_type num)
{
    /*@formatter:off*/
   spTransformAddKernel<<<num/256+1,256>>>(v,a,b,num);
    /*@formatter:on*/
    return SP_SUCCESS;

}

int spExclusiveScan(size_type const *b, size_type const *e, size_type *out)
{
    try
    {
        thrust::exclusive_scan(
                thrust::device_ptr<size_type>((size_type *) b),
                thrust::device_ptr<size_type>((size_type *) e),
                thrust::device_ptr<size_type>(out)
        );
    }
    catch (...)
    {
        return SP_FAILED;
    }

    return SP_SUCCESS;
};

int spInclusiveScan(size_type const *b, size_type const *e, size_type *out)
{
    try
    {
        thrust::inclusive_scan(
                thrust::device_ptr<size_type>((size_type *) b),
                thrust::device_ptr<size_type>((size_type *) e),
                thrust::device_ptr<size_type>(out)
        );
    }
    catch (...)
    {
        return SP_FAILED;
    }


    return SP_SUCCESS;
};


__global__ void
spPackInt_kernel(size_type *dest, size_type const *src,
                 size_type const *dest_start, size_type const *src_start, size_type const *count)
{

    uint s = threadIdx.x;
    while (s < count[blockIdx.x])
    {
        dest[dest_start[blockIdx.x] + threadIdx.x] = src[src_start[blockIdx.x] + threadIdx.x];
        s += blockDim.x;
    }

}

int spPackInt(size_type **dest, size_type *num, size_type const *src,
              size_type num_of_cell, size_type const *start, size_type const *count)
{
    if (num_of_cell == 0) { return SP_SUCCESS; }

    size_type * dest_start;

    SP_CALL(spMemoryDeviceAlloc((void **) &dest_start, (num_of_cell + 1) * sizeof(size_type)));

    SP_CALL(spInclusiveScan(count, count + num_of_cell, dest_start + 1));

    SP_CALL(spMemoryCopy(num, &(dest_start[num_of_cell]), sizeof(size_type)));

    SP_CALL(spMemorySet(dest_start, 0, sizeof(size_type)));

    SP_CALL(spMemoryDeviceAlloc((void **) dest, (*num) * sizeof(size_type)));

    SP_CALL_DEVICE_KERNEL(spPackInt_kernel, num_of_cell, 256, *dest, src, dest_start, start, count);

    SP_CALL(spMemoryDeviceFree((void **) &dest_start));

    return SP_SUCCESS;
}