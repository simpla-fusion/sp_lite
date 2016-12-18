//
// Created by salmon on 16-7-28.
//
#include <stdlib.h>
#include <string.h>
#include "../../spParallel.h"
#include "spParallelOPENMP.h"

#include <omp.h>

int spParallelDeviceInitialize(int argc, char **argv)
{
#ifndef NDEBUG
    omp_set_num_threads(1);
#endif
    return SP_SUCCESS;
}

int spParallelDeviceFinalize() { return SP_SUCCESS; }

int spMemoryDeviceAlloc(void **p, size_type s)
{
    *p = malloc(s);
    return SP_SUCCESS;
}

int spMemoryDeviceFree(void **p)
{
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
    return SP_SUCCESS;
};

int spMemoryCopy(void *dest, void const *src, size_type s)
{
    memcpy(dest, src, s);
    return SP_SUCCESS;
}

int spMemoryCopyToCache(const void *dest, void const *src, size_type s)
{
    memcpy((void *) dest, src, s);
    return SP_SUCCESS;
}

int spMemorySet(void *dest, int v, size_type s)
{
    memset(dest, v, s);
    return SP_SUCCESS;
}

int spParallelDeviceSync()
{
    SP_CALL(spParallelGlobalBarrier());
    return SP_SUCCESS;
}

int spMemoryHostAlloc(void **p, size_type s)
{
    *p = malloc(s);
    return SP_SUCCESS;
};

int spMemoryHostFree(void **p)
{
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
    return SP_SUCCESS;
}

int spParallelDeviceFillInt(int *d, int v, size_type s)
{
    UNIMPLEMENTED;
    return SP_SUCCESS;
};


int spParallelDeviceFillReal(Real *d, Real v, size_type s)
{
    UNIMPLEMENTED;
    return SP_SUCCESS;
};


int spParallelAssign(size_type num_of_point, size_type *offset, Real *d, Real const *v)
{
    UNIMPLEMENTED;
    return SP_SUCCESS;
};

int spMemoryDeviceToHost(void **p, void *src, size_type size_in_byte)
{
    *p = src;
    return SP_SUCCESS;
}
int spMemoryHostFree(void **p)
{
    *p = NULL;
    return SP_SUCCESS;
};

