
FIND_PACKAGE(CUDA 7.5)
IF (CUDA_FOUND)
    SET(CUDA_HOST_COMPILER ${CMAKE_C_COMPILER})

    INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})

    SET(CUDA_SEPARABLE_COMPILATION ON)

    SET(CUDA_NVCC_FLAGS -arch=sm_30 -maxrregcount=32 -lineinfo)

    ADD_DEFINITIONS(-DUSE_CUDA -DNUMBER_OF_THREADS_PER_BLOCK=256)

    FILE(GLOB sp_lite_SRC_CU ./*.cu)

    CUDA_ADD_LIBRARY(sp_lite_cuda ${sp_lite_SRC_CU})
    TARGET_LINK_LIBRARIES(sp_lite_cuda pthread ${CUDA_curand_LIBRARY})
ENDIF (CUDA_FOUND)
